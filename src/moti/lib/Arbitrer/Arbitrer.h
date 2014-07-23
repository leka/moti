#ifndef LEKA_MOTI_ARDUINO_ARBITRER_H_
#define LEKA_MOTI_ARDUINO_ARBITRER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"


typedef enum {
	SLEEPING = 0x01,
	SEEKING_INTERACTION = 0x02,
	CRUISING = 0x04,
	REORIENTING = 0x08
} ArbitrerState;


class Arbitrer {
	public:
		static void launch(void);
		static void stop(void);

	private:
		static void start(void* arg=NULL, tprio_t priority=NORMALPRIO);

		static bool _isStarted, _isRunning;

		static bool _isCruising;

		static ArbitrerState _state;

		static Semaphore _sem;
		static msg_t thread(void* arg);
};


bool Arbitrer::_isStarted = false;
bool Arbitrer::_isRunning = false;
bool Arbitrer::_isCruising = false;
ArbitrerState Arbitrer::_state = SLEEPING;
Semaphore Arbitrer::_sem = _SEMAPHORE_DATA(Arbitrer::_sem, 0);


static WORKING_AREA(arbitrerThreadArea, 512);


void Arbitrer::launch(void) {
	if (!_isStarted)
		Arbitrer::start();

	if (!_isRunning) {
		_isRunning = true;
		chSemSignal(&_sem);
	}
}

void Arbitrer::stop(void) {
	if (!_isStarted)
		Arbitrer::start();

	if (_isRunning)
		_isRunning = false;
}


void Arbitrer::start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(arbitrerThreadArea, sizeof(arbitrerThreadArea),
				priority, thread, arg);
	}
}

msg_t Arbitrer::thread(void* arg) {
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
					for (uint8_t i = 0; i < 4; ++i) {						
						DriveSystem::spin(i % 2 == 0 ? LEFT : RIGHT, 200, 1.0);

						while (DriveSystem::getState() != NONE)
							waitMs(15);

						waitMs(500);
					}

					waitMs(2000);
					_state = CRUISING;

					break;

				case CRUISING:
					if (Light::getState(HEART) == INACTIVE)
					 	Light::fade(HEART, Color::GreenPure, Color::GreenPure, 1500);

					if (!_isCruising) {
						_isCruising = true;
						cruiseStart = millis();
						DriveSystem::go(FORWARD, 120, 0);
					}

					if (Environment::isStuck() && (cruiseStart + 1000 < millis())) {
						DriveSystem::stop(0);
						while (DriveSystem::getState() != NONE)
							waitMs(15);

						DriveSystem::spin(rand() % 2 == 0 ? LEFT : RIGHT, 120, 1.57f);

						spinStart = millis();

						_isCruising = false;
						_state = REORIENTING;
					}

					break;

				case REORIENTING:
					if (Light::getState(HEART) == INACTIVE)
					 	Light::fade(HEART, Color::RedPure, Color::RedPure, 1500);

					if ((DriveSystem::getState() == NONE) && (spinStart + 100 < millis())) {
						_state = CRUISING;
					}

					break;
			}

			waitMs(50);
		}
	}

    return (msg_t)0;
}


#endif
