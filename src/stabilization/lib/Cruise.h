#ifndef LEKA_MOTI_CRUISE_H
#define LEKA_MOTI_CRUISE_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"
#include "DriveSystem.h"

void cruiseTask() {
	heart.fade(500, RAND, RAND);
}

static msg_t CruiseThread(void *arg) {
	(void)arg;

	CruiseThd = chThdSelf();

	while(TRUE) {
		// chEvtWaitAny(cruiseEvent);
		// if (!sleeping)
			cruiseTask();

		chThdSleepMilliseconds(70);
	}

  return (msg_t)0;
}

#endif // LEKA_MOTI_CRUISE_H
