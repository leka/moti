#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t SensorThreadFunction(void *arg) {
	(void)arg;

	systime_t nextTime = chTimeNow();

	while (TRUE) {
		nextTime += MS2ST(100);
		sensors.read();
		chSemSignal(&ArbitrerSem);
		chThdSleepUntil(nextTime);
	}
	return 0;
}