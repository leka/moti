#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t HeartThreadFunction(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10; // divide by ten to have a wait delay higher than 1ms
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 150;

	while (TRUE) {
		// serial.println("Heart");

		heart.fade(40, basePwm, P, 0, 0, 0, 0);
		heart.fade(40, P, basePwm, 0, 0, 0, 0);

		heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(80);

		heart.fade(60, Q, R, 0, 0, 0, 0);
		heart.fade(70, R, basePwm, 0, 0, 0, 0);

		chThdSleepMilliseconds(30000/ _bpm);
	}
	return 0;
}


