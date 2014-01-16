#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t DriveThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {

		chSemWait(&DriveSem);

		if (getBehavior() == WAKE_UP) {
			driveSystem.spin(RIGHT);
			chThdSleepMilliseconds(1000);
			driveSystem.spin(LEFT);
			chThdSleepMilliseconds(1000);

			driveSystem.stop();

			setBehavior(EXPLORE);
		}

		else if (getBehavior() == EXPLORE) {
			chThdSleepMilliseconds(2000);
			driveSystem.go();
			chThdSleepMilliseconds(1000);
			driveSystem.turn(RIGHT);
			chThdSleepMilliseconds(1000);
			driveSystem.go();
			chThdSleepMilliseconds(1000);
			driveSystem.turn(LEFT);
			chThdSleepMilliseconds(1000);
			driveSystem.spin();
			chThdSleepMilliseconds(200);
			driveSystem.go();
			chThdSleepMilliseconds(800);

			driveSystem.stop();

			chMtxLock(&WaitingTimeMutex);
				_startWaitingTime = chTimeNow();
			chMtxUnlock();

			setBehavior(WAITING);
		}

		else if (getBehavior() == WAITING) {
			driveSystem.stop();
			chThdSleepMilliseconds(1500);
		}

		else if (getBehavior() == WANT_INTERACTION) {
			driveSystem.go();
			chThdSleepMilliseconds(300);
			driveSystem.stop();
			driveSystem.go();
			chThdSleepMilliseconds(300);
			driveSystem.stop();
			driveSystem.go();
			chThdSleepMilliseconds(300);
			driveSystem.stop();

			setBehavior(WAITING);
		}

		else if (getBehavior() == SLEEP) {
			driveSystem.stop();
		}
	}
	return 0;
}


