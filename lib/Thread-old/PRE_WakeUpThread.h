#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static msg_t WakeUpThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {
		chSemWait(&WakeUpSem);

		sleep.fade(400, BLUE, PURPLE);
		sleep.fade(200, PURPLE, BLUE);
		sleep.fade(400, BLUE, ORANGE);
		sleep.fade(200, ORANGE, PINK);
		sleep.fade(400, BLUE, ORANGE);
		sleep.fade(200, ORANGE, PINK);

		sleep.fade(400, RAND, RAND);
		sleep.fade(200, RAND, RAND);
		sleep.fade(400, RAND, RAND);
		sleep.fade(200, RAND, RAND);

		sleep.turnOff();
		chThdSleepMilliseconds(100);

		sleep.shine(RAND);

		driveSystem.go();
		chThdSleepMilliseconds(1500);

	}
	return 0;
}


