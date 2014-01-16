#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t DriveThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {

		if (getBehavior() == WAKE_UP) {
			serial.println("Wake up movements start");
			chThdSleepMilliseconds(2000);
			serial.println("Wake up movements end");
		}
		if (getBehavior() == EXPLORE) {
			serial.println("Explore movements start");
			chThdSleepMilliseconds(2000);
			serial.println("Explore movements end");
		}
		if (getBehavior() == WAITING) {
			serial.println("Waiting movements start");
			chThdSleepMilliseconds(2000);
			serial.println("Waiting movements end");
		}
		if (getBehavior() == WANT_INTERACTION) {
			serial.println("Want interaction movements start");
			chThdSleepMilliseconds(2000);
			serial.println("Want interaction movements end");
		}
		if (getBehavior() == SLEEP) {
			serial.println("Sleep movements start");
			chThdSleepMilliseconds(2000);
			serial.println("Sleep movements end");
		}
	}
	return 0;
}


