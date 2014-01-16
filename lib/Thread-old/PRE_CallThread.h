#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static msg_t CallThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&CallSem);
		serial.println("I'm calling out !");
		chThdSleepMilliseconds(1000);
		serial.println("Is there anybody out there?");
	}

	return 0;
}