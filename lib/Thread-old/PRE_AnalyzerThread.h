#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Thread.h"

static msg_t AnalyzerThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&AnalyzerSem);

		// are we at startup?
		if (isStarting) {
			isStarting = FALSE;
			chSemSignal(&WakeUpSem);
		}

		// is x to high ?
		if (sensors.getXYZ(0) > 300) {
			chSemSignal(&ExploreSem);
		}

	}
}