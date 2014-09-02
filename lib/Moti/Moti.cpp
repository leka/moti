#include "Moti.h"
#include "ChibiOS_AVR.h"

#define HISTORY_SIZE 6

void waitMs(uint16_t ms) {
	chThdSleepMilliseconds(ms);
}

namespace Moti {

	bool _isStarted = false;
	bool _isRunning = false;
	bool _isStuck = false;
	bool _isShaken= false;
	uint32_t _startStuckTime = 0;
	bool _isSpinning = false;
	float _spinAngle = 0.f;
	int16_t _nLaps = 0;


	float spinHistory[HISTORY_SIZE] = { 0.f };

	msg_t thread(void* arg);

	static WORKING_AREA(environmentThreadArea, 256);


	/**
	 * @brief Tells the Environment thread to run and check for events
	 */
	void run(void) {
		_isRunning = true;
		Serial.println(10);
	}

	/**
	 * @brief Tells the Environment thread to stop checking for event
	 */
	void stop(void) {
		_isRunning = false;
		_isStuck = false;
	}

	/**
	 * @brief Returns whether the device is stuck or not
	 * @return true if it is stuck, false otherwise
	 */
	bool isStuck() {
		if (!_isStarted)
			start();

		return _isStuck && (abs(millis() - _startStuckTime) > ENVIRONMENT_STUCK_TIME);
	}

	bool isShaken(void) {
		return _isShaken;	
	}

	bool isSpinning(void) {
		return _isSpinning;
	}

	uint8_t countSpinLaps(void) {
		return (uint8_t)abs(_nLaps);
	}


	void start(void* arg, tprio_t priority) {
		if (!_isStarted) {
			_isStarted = true;

			(void)chThdCreateStatic(environmentThreadArea,
					sizeof(environmentThreadArea),
					priority, thread, arg);

		}
	}

	float mod(float a, float b) {
		float m = (float)fmod((double)a, (double)b);

		if (m < 0.f) {
			m += b;
		}

		return m;
	}

	float _diffAngle(float a, float b) {
		float diff = a - b;

		return mod(diff + 180.f, 360.f) - 180.f;
	}

	float _arrayDeltaSum(float* array, uint8_t size) {
		float sum = abs(_diffAngle(array[0], array[size - 1]));

		for (uint8_t i = 1; i < size; ++i)
			sum += abs(_diffAngle(array[i], array[i - 1]));

		return sum;
	}

	msg_t thread(void* arg) {
		uint8_t i = 0;

		float currentAngle = 0.f;
		float oldAngle = 0.f;

		while (!chThdShouldTerminate()) {
			if (_isRunning) {

				if (abs(Sensors::getAccX()) > ENVIRONMENT_STUCK_THRESHOLD) {
					if (!_isStuck) {
						_isStuck = true;
						_startStuckTime = millis();
					}
				}
				else
					_isStuck = false;


				oldAngle = currentAngle;
				currentAngle = Sensors::getEulerPhiDeg();
				spinHistory[i] = currentAngle;
				i = (i + 1) % HISTORY_SIZE;

				if (abs(_arrayDeltaSum(spinHistory, HISTORY_SIZE)) > 15.f)
					_isSpinning = true;
				else {
					_isSpinning = false;
					_nLaps = 0;
				}

				if (_isSpinning) {
					if ((currentAngle * oldAngle < 0.f) && (currentAngle * oldAngle > -8000.f)) {
						if (currentAngle > 0.f)
							_nLaps++;
						else
							_nLaps--;
					}
				}
			}

			waitMs(ENVIRONMENT_THREAD_DELAY);
		}

		return (msg_t)0;
	}

}
