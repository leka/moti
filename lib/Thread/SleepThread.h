#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static WORKING_AREA(waSleepThread, 260);

static msg_t SleepThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 0; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
	volatile uint8_t R = 250;

	while (TRUE) {

		sleep.fade(1300, 0, 0, 0, 0, basePwm, R);

		sleep.fade(650, 0, 0, 0, 0, R, basePwm);

		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}


