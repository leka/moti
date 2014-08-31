#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Moti.h"

namespace Stabilization {

	// Functions
	void start(void* arg=NULL, tprio_t priority=NORMALPRIO);
	void run(void);
	void stop(void);

	// Variables
	bool _isStarted = false;
	bool _isRunning = false;

}

static WORKING_AREA(stabilizationThreadArea, 256);

namespace Stabilization {

	static msg_t thread(void* arg);

	// Definition of the start() procedure
	void start(void* arg, tprio_t priority) {
		if (!_isStarted) {
			_isStarted = true;
			_isRunning = true;

			(void)chThdCreateStatic(stabilizationThreadArea,
					sizeof(stabilizationThreadArea),
					priority, thread, arg);
		}
	}

	// Definition of the run() procedure
	void run(void) {
		if (!_isStarted)
			start(NULL, NORMALPRIO);

		_isRunning = true;
	}

	// Definition of the stop() procedure
	void stop(void) {
		_isRunning = false;
	}

	msg_t thread(void* arg) {

		(void) arg;

		float inputValue = 0.f;             // Define variables
		float outputValue = 0.f;

		float accY = 0.f;                   // The Y-axis accelerometer value
		Rotation spinDirection;        // Spin direction i.e. left or right

		Direction direction;
		uint8_t speed;

		while (!chThdShouldTerminate()) {

			if (_isRunning) {
				inputValue = Sensors::getAccX();  // Get the value of the X-axis
				outputValue = 0.5 * inputValue;   // Compute the output value

				accY = Sensors::getAccY();        // Get the value of the Y-axis

				if (abs(outputValue) > 100.f) {
					direction = outputValue < 0.f ? BACKWARD : FORWARD;    // Select the direction
					speed = (uint8_t)abs(outputValue);

					Motion::go(direction, speed, 100);    // Turn the motors on for 100ms at the desired speed
				}
				else if (abs(accY) > 80.f) {
					spinDirection = accY > 0.f ? RIGHT : LEFT;

					Motion::spinDeg(spinDirection, 130, 90);       // Spin 90 degrees with an arbitrary speed of 130
				}
			}

			waitMs(50); // Prevents us from taking all the CPU

		}

		return (msg_t)0;
	}
}
