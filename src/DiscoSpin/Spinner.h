#ifndef LEKA_MOTI_BEHAVIOR_SPINNER_H_
#define LEKA_MOTI_BEHAVIOR_SPINNER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Light.h"
#include "Wander.h"

namespace Spinner {

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

void Spinner::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void Spinner::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void Spinner::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;

	chMtxUnlock();
}

msg_t Spinner::thread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			Serial.println(F("S1"));
			DriveSystem::stop();
			waitMs(1000);
			DriveSystem::spin(LEFT, 190);
			waitMs(random(2000, 5000));
			DriveSystem::stop();
			waitMs(random(2000, 5000));
			DriveSystem::spin(RIGHT, 190);
			waitMs(random(2000, 5000));
			DriveSystem::stop();
			waitMs(2000);

			stop();

			Wander::start();
			Serial.println(F("S2"));
		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

#endif
