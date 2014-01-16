#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t ArbitrerThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&ArbitrerSem);

		// is x to high ?
		if (sensors.getXYZ(0) > 300) {
			setBehavior(WANT_INTERACTION);
		}

		// are we at startup?
		if (sensors.getXYZ(1) > 300) {
			setBehavior(EXPLORE);
		}

		if (sensors.getXYZ(2) < -300) {
			setBehavior(SLEEP);
		}

		// chSemSignal(&DriveSem);
		// chSemSignal(&LightSem);
	}
}