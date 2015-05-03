#ifndef LEKA_MOTI_BEHAVIOR_STABILIZATION_H_
#define LEKA_MOTI_BEHAVIOR_STABILIZATION_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Motion.h"

namespace Stabilization {

	// Thread methods
	static WORKING_AREA(stabilizationThreadArea, 256);
	static msg_t thread(void* arg);

	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;
	uint8_t _threadDelay = 100;
	uint32_t _runStartTime = 0;

	// Misc
	MUTEX_DECL(_stabMutex);

}

void Stabilization::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;

		(void)chThdCreateStatic(stabilizationThreadArea,
				sizeof(stabilizationThreadArea),
				priority, thread, arg);
	}
}

void Stabilization::start(void) {
	chMtxLock(&_stabMutex);

	_isStarted = true;
	_runStartTime = millis();

	chMtxUnlock();
}

void Stabilization::stop(void) {
	chMtxLock(&_stabMutex);

	_isStarted = false;

	chMtxUnlock();
}

msg_t Stabilization::thread(void* arg) {

	(void) arg;

	float currentAngle = 0.0;
	float input = 0.0;
	int16_t output = 0.0;

	uint8_t speed = 0;
	int16_t accY = 0;

	uint32_t currentTime = 0;

	while (!chThdShouldTerminate()) {
		if (_isStarted) {

			currentTime = abs(millis() - _runStartTime);

			input = Sensors::getAccX();
			output = (-0.7 * input);
			accY = Sensors::getAccY();

			if (currentTime > 2000) {
				currentAngle = Sensors::getEulerPsi();
			}

			if (abs(output) > 80.0) {
				speed = (uint8_t)abs(output);
				DriveSystem::go(output < 0 ? BACKWARD : FORWARD, speed);
			}
			else if (abs(accY) > 80) {
				Motion::spin(accY > 0 ? RIGHT : LEFT, 120, 1.57);
			}
			else if ((currentTime > 2000) && abs(currentAngle) > 0.40) {
				speed = (uint8_t)min(230, 100 + abs(currentAngle) * 80);
				Motion::spin(currentAngle > 0.0f ? LEFT : RIGHT, speed, abs(currentAngle));
			}
			else if (Motion::getState() != NONE) {
				Motion::stop(0);
			}
			else {
				DriveSystem::stop();
			}
		}

		waitMs(_threadDelay);

	}

	return (msg_t)0;
}

#endif
