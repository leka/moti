#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static msg_t WakeUpThreadFunction(void *arg) {

	(void)arg;

	while (TRUE) {
		chSemWait(&WakeUpSem);
		serial.println("Time to wake up!");
		chThdSleepMilliseconds(1000);
		serial.println("Now I'm fine!");
	}
	return 0;
}


