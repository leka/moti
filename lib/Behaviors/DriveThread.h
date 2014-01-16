#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t DriveThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {

		chSemWait(&DriveSem);

		// serial.println("Drive");

		// driveSystem.stop();
		// light.turnOff();

		if (getBehavior() == WAKE_UP) {
			// serial.println("Wake up movements start");
			chThdSleepMilliseconds(2000);
			// serial.println("Wake up movements end");
			setBehavior(EXPLORE);
		}
		else if (getBehavior() == EXPLORE) {
			// serial.println("Explore movements start");
			chThdSleepMilliseconds(5000);
			// serial.println("Explore movements end");
			setBehavior(WAITING);
			_startWaitingTime = chTimeNow();
		}
		else if (getBehavior() == WAITING) {
			driveSystem.stop();
		}
		else if (getBehavior() == WANT_INTERACTION) {
			// driveSystem.go();
			// chThdSleepMilliseconds(300);
			// driveSystem.go();
			// chThdSleepMilliseconds(300);
			// driveSystem.go();
			// chThdSleepMilliseconds(300);
		}
		else if (getBehavior() == SLEEP) {
			driveSystem.stop();
		}
	}
	return 0;
}


