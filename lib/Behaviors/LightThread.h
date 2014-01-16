#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t LightThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {
		if (getBehavior() == WAKE_UP) {
			serial.println("Wake up light start");
			chThdSleepMilliseconds(2000);
			serial.println("Wake up light end");
		}
		if (getBehavior() == EXPLORE) {
			serial.println("Explore light start");
			chThdSleepMilliseconds(2000);
			serial.println("Explore light end");
		}
		if (getBehavior() == WAITING) {
			serial.println("Waiting light start");
			chThdSleepMilliseconds(2000);
			serial.println("Waiting light end");
		}
		if (getBehavior() == WANT_INTERACTION) {
			serial.println("Want interaction light start");
			chThdSleepMilliseconds(2000);
			serial.println("Want interaction light end");
		}
		if (getBehavior() == SLEEP) {
			serial.println("Sleep light start");

			volatile uint8_t basePwm = 0; // divided by ten to have a wait delay higher than 1ms
			volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
			volatile uint8_t R = 250;

			light.fade(1300, 0, 0, 0, 0, basePwm, R);
			light.fade(650, 0, 0, 0, 0, R, basePwm);

			chThdSleepMilliseconds(30000/ bpm);

			serial.println("Sleep light end");
		}
	}
	return 0;
}


