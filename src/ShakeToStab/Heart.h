#ifndef LEKA_MOTI_BEHAVIOR_BEHAVIOR_NAME_H_
#define LEKA_MOTI_BEHAVIOR_BEHAVIOR_NAME_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Light.h"

namespace Heart {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;
	uint16_t _behaviorThreadDelay = 2000;

	// Misc
	MUTEX_DECL(_behaviorMutex);

}

void Heart::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;
		_isStarted = false;

		(void)chThdCreateStatic(behaviorThreadArea,
				sizeof(behaviorThreadArea),
				priority, thread, arg);
	}
}

void Heart::start(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = true;

	chMtxUnlock();
}

void Heart::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;
	Light::fade(HEART, Color::Black, Color::Black, _behaviorThreadDelay);

	chMtxUnlock();
}

msg_t Heart::thread(void* arg) {

	(void) arg;

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 230;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			Light::fade(HEART, Color(basePwm, 0, 0), Color(P, 0, 0), 100);
			Light::fade(HEART, Color(P, 0, 0), Color(basePwm, 0, 0), 100);

			Light::fade(HEART, Color(basePwm, 0, 0), Color(basePwm, 0, 0), 160);

			Light::fade(HEART, Color(Q, 0, 0), Color(R, 0, 0), 120);
			Light::fade(HEART, Color(R, 0, 0), Color(basePwm, 0, 0), 140);

		}

		waitMs(_behaviorThreadDelay);
	}
	return (msg_t)0;
}

#endif
