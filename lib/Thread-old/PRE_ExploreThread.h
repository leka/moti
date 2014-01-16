#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static msg_t ExploreThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&ExploreSem);
		serial.println("Start of Explore Function");
		chThdSleepMilliseconds(1000);
		serial.println("End of Explore Function");
	}

	return 0;
}