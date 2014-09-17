#ifndef LEKA_MOTI_BEHAVIOR_BEHAVIOR_NAME_H_
#define LEKA_MOTI_BEHAVIOR_BEHAVIOR_NAME_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

namespace BehaviorName {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;
	uint16_t _behaviorThreadDelay = 50;

	// Misc
	MUTEX_DECL(_behaviorMutex);

}

void BehaviorName::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void BehaviorName::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void BehaviorName::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;

	chMtxUnlock();
}

msg_t BehaviorName::thread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			// do things here

		}

		waitMs(_behaviorThreadDelay);
	}
	return (msg_t)0;
}

#endif
