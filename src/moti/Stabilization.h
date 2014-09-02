#ifndef LEKA_MOTI_BEHAVIOR_STABILIZATION_H_
#define LEKA_MOTI_BEHAVIOR_STABILIZATION_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"

namespace Stabilization {

	void start(void* arg=NULL, tprio_t priority=NORMALPRIO);

	void run(void);
	void stop(void);

}

static WORKING_AREA(stabilizationThreadArea, 256);

namespace Stabilization {

	bool _isStarted = false;
	bool _isRunning = false;

	uint32_t _runStartTime = 0;

	static msg_t thread(void* arg);

	MUTEX_DECL(_stabMutex);

void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;
		_isRunning = true;

		(void)chThdCreateStatic(stabilizationThreadArea,
				sizeof(stabilizationThreadArea),
				priority, thread, arg);
	}
}

void run(void) {
	chMtxLock(&_stabMutex);

	_isRunning = true;
	_runStartTime = millis();

	chMtxUnlock();
}

void stop(void) {
	chMtxLock(&_stabMutex);

	_isRunning = false;

	chMtxUnlock();
}

msg_t thread(void* arg) {
	float currentAngle = 0.0;
	float input = 0.0;
	int16_t output = 0.0;

	uint8_t speed = 0;
	int16_t accY = 0;

	uint32_t currentTime = 0;

	while (!chThdShouldTerminate()) {
		if (_isRunning) {
			currentTime = abs(millis() - _runStartTime);
			if (currentTime > 2000)
				currentAngle = Sensors::getEulerPhi();

			input = Sensors::getAccX();
			output = (int16_t)(-0.5 * input);

			if (abs(output) > 80.0) {
				speed = (uint8_t)abs(output);
				Motion::go(output < 0 ? BACKWARD : FORWARD, speed, 100);
			}
			else {
				accY = Sensors::getAccY();

				if (abs(accY) > 80)
					Motion::spin(accY > 0 ? RIGHT : LEFT, 105, 1.57);

				else if ((currentTime > 2000) && abs(currentAngle) > 0.40) {
					speed = (uint8_t)min(255, 100 + abs(currentAngle) * 80);
					Motion::spin(currentAngle > 0.0f ? LEFT : RIGHT, speed, abs(currentAngle));
				}

				else if (Motion::getState() != NONE)
					Motion::stop(0);
			}
		}

		waitMs(STABILIZATION_THREAD_DELAY);
	}

	return (msg_t)0;
}

}

#endif
