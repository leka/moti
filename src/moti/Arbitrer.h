#ifndef LEKA_MOTI_BEHAVIOR_ARBITRER_H_
#define LEKA_MOTI_BEHAVIOR_ARBITRER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Moti.h"


typedef enum {
	SLEEPING = 0x01,
	SEEKING_INTERACTION = 0x02,
	CRUISING = 0x04,
	REORIENTING = 0x08
} ArbitrerState;


namespace Arbitrer {

	void launch(void);
	void stop(void);

	void start(void* arg=NULL, tprio_t priority=NORMALPRIO);

}


static WORKING_AREA(arbitrerThreadArea, 512);

namespace Arbitrer {

	bool _isStarted = false;
	bool _isRunning = false;
	bool _isCruising = false;
	ArbitrerState _state = SLEEPING;

	Semaphore _sem = _SEMAPHORE_DATA(_sem, 0);
	static msg_t thread(void* arg);

	MUTEX_DECL(_arbitrerMutex);


	void launch(void) {
		if (!_isStarted)
			start();

		chMtxLock(&_arbitrerMutex);

		Moti::start();

		if (!_isRunning) {
			_isRunning = true;
			chSemSignal(&_sem);
		}

		chMtxUnlock();
	}

	void stop(void) {
		if (!_isStarted)
			start();

		chMtxLock(&_arbitrerMutex);

		Moti::stop();

		if (_isRunning) {
			_state = SLEEPING;
			_isCruising = false;
			_isRunning = false;
		}

		chMtxUnlock();
	}


	void start(void* arg, tprio_t priority) {
		if (!_isStarted) {
			_isStarted = true;

			(void)chThdCreateStatic(arbitrerThreadArea, sizeof(arbitrerThreadArea),
					priority, thread, arg);
		}
	}

	msg_t thread(void* arg) {
		uint16_t spinStart = 0;
		uint16_t cruiseStart = 0;

		while (!chThdShouldTerminate()) {
			chSemWait(&_sem);

			while (_isRunning) {
				switch (_state) {
					case SLEEPING: /* TODO : Seek interaction */
						_state = SEEKING_INTERACTION;
						break;

					case SEEKING_INTERACTION:
						/* for (uint8_t i = 0; i < 4; ++i) {
						   DriveSystem::spin(i % 2 == 0 ? LEFT : RIGHT, 200, 1.0);

						   while ((_state == SEEKING_INTERACTION) && (DriveSystem::getState() != NONE))
						   waitMs(15);

						   waitMs(500);
						   }

						   waitMs(2000); */

						chMtxLock(&_arbitrerMutex);
						_state = CRUISING;
						chMtxUnlock();

						break;

					case CRUISING:
						if (Light::getState(HEART) == INACTIVE)
							Light::fade(HEART, Color::GreenPure, Color::GreenPure, 1500);

						chMtxLock(&_arbitrerMutex);

						if (!_isCruising) {
							_isCruising = true;
							cruiseStart = millis();
							Motion::go(FORWARD, 105, 0);
						}

						chMtxUnlock();


						if (Moti::isStuck() && (cruiseStart + 1000 < millis())) {
							Motion::stop(0);
							while ((_state == CRUISING) && (Motion::getState() != NONE))
								waitMs(15);

							Motion::spin(rand() % 2 == 0 ? LEFT : RIGHT, 100, 1.57f);

							spinStart = millis();

							chMtxLock(&_arbitrerMutex);
							_isCruising = false;
							_state = REORIENTING;
							chMtxUnlock();
						}

						break;

					case REORIENTING:
						if (Light::getState(HEART) == INACTIVE)
							Light::fade(HEART, Color::RedPure, Color::RedPure, 1500);


						chMtxLock(&_arbitrerMutex);

						if ((Motion::getState() == NONE) && (spinStart + 100 < millis())) {
							_state = CRUISING;
						}
						else if ((Motion::getState() != NONE) && (spinStart + 1200 < millis())) {
							_state = CRUISING;
						}

						chMtxUnlock();

						break;
				}

				waitMs(50);
			}
		}

		return (msg_t)0;
	}

}

#endif
