#ifndef LEKA_MOTI_BEHAVIOR_MOVER_H_
#define LEKA_MOTI_BEHAVIOR_MOVER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Sensors.h"
// #include "Motion.h"
#include "DriveSystem.h"
#include "Light.h"

namespace Mover {

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

	// Misc
	MUTEX_DECL(_behaviorMutex);

}

void Mover::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void Mover::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void Mover::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;

	chMtxUnlock();
}

msg_t Mover::thread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			Serial.println(F("M1"));
			DriveSystem::go(FORWARD, 190);
			waitMs(10000);
			DriveSystem::stop();
			waitMs(5000);
			DriveSystem::spin(LEFT, 190);
			waitMs(500);
			DriveSystem::stop();
			waitMs(5000);
			Serial.println(F("M2"));
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

#endif
