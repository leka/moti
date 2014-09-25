#ifndef LEKA_MOTI_BEHAVIOR_WANDER_H_
#define LEKA_MOTI_BEHAVIOR_WANDER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "Motion.h"
#include "Light.h"

namespace Wander {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);
	uint16_t _threadDelay = 50;

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;

	bool _isMoving = false;

	// Misc
	MUTEX_DECL(_behaviorMutex);

}

void Wander::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void Wander::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void Wander::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;

	chMtxUnlock();
}

msg_t Wander::thread(void* arg) {

	(void) arg;

	uint16_t moveStart = 0;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			if (!_isMoving) {
				chMtxLock(&_behaviorMutex);
				_isMoving = true;
				moveStart = millis();
				Motion::go(FORWARD, 150, 0);
				chMtxUnlock();
			}

			if (Moti::isStuck() && (moveStart + 1000 < millis())) {

				_isMoving = false;

				Motion::stop(0);

				waitMs(1000);

				Motion::spinDeg(rand() % 2 == 0 ? LEFT : RIGHT, 125, 100);

				waitMs(1000);

				Motion::stop(0);

				waitMs(1000);

			}

		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

#endif
