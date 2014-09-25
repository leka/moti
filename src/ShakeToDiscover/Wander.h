#ifndef LEKA_MOTI_BEHAVIOR_WANDER_H_
#define LEKA_MOTI_BEHAVIOR_WANDER_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Sensors.h"
#include "Motion.h"
#include "Light.h"

typedef enum {
	SLEEPING = 0x01,
	MOVING = 0x02,
	REORIENTING = 0x03,
	STABILIZING = 0x04
} MovementState;

namespace Wander {

	// Thread methods
	static WORKING_AREA(behaviorThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);
	uint16_t _behaviorThreadDelay = 50;

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;

	MovementState _movementState = MOVING;
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
	_movementState = MOVING;

	chMtxUnlock();
}

void Wander::stop(void) {
	chMtxLock(&_behaviorMutex);

	_isStarted = false;
	_movementState = SLEEPING;

	chMtxUnlock();
}

msg_t Wander::thread(void* arg) {

	(void) arg;

	uint16_t spinStart = 0;
	uint16_t moveStart = 0;

	while (!chThdShouldTerminate()) {

		Serial.println("Before if");
		if (_isStarted) {

			Serial.println("Before Switch");

			switch (_movementState) {

				case SLEEPING:
					Serial.println("Sleep");
					break;

				case STABILIZING:
					Serial.println("Stab");
					break;

				case MOVING:
					// if (Light::getState(HEART) == INACTIVE)
					// 	Light::fade(HEART, Color::GreenPure, Color::GreenPure, 1500);
					//
					Serial.println("Moving");

					chMtxLock(&_behaviorMutex);

					if (!_isMoving) {
						_isMoving = true;
						moveStart = millis();
						Motion::go(FORWARD, 105, 0);
					}

					chMtxUnlock();


					if (Moti::isStuck() && (moveStart + 1000 < millis())) {
						Motion::stop(0);
						while ((_movementState == MOVING) && (Motion::getState() != NONE))
							waitMs(15);

						Motion::spin(rand() % 2 == 0 ? LEFT : RIGHT, 100, 1.57f);

						spinStart = millis();

						chMtxLock(&_behaviorMutex);
						_isMoving = false;
						_movementState = REORIENTING;
						chMtxUnlock();
					}

					break;

				case REORIENTING:
					// if (Light::getState(HEART) == INACTIVE)
					// 	Light::fade(HEART, Color::RedPure, Color::RedPure, 1500);
					//

					Serial.println("Reorient");
					chMtxLock(&_behaviorMutex);

					if ((Motion::getState() == NONE) && (spinStart + 100 < millis())) {
						_movementState = MOVING;
					}
					else if ((Motion::getState() != NONE) && (spinStart + 1200 < millis())) {
						_movementState = MOVING;
					}

					chMtxUnlock();

					break;
			}

		}
	}

	waitMs(_behaviorThreadDelay);

	return (msg_t)0;
}

#endif
