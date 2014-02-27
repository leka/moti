#ifndef LEKA_MOTI_CRUISE_H
#define LEKA_MOTI_CRUISE_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"
#include "DriveSystem.h"

void cruiseTask() {
	heart.shine(GREEN_PURE);
	Serial.println(F("Cruising..."));
	robot.go();
	chThdSleepMilliseconds(4000);
}

static msg_t CruiseThread(void *arg) {
	(void)arg;

	CruiseThd = chThdSelf();

	while(TRUE) {
		// chEvtWaitAny(cruiseEvent);
		cruiseTask();
	}
}

#endif // LEKA_MOTI_CRUISE_H