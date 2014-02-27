#ifndef LEKA_MOTI_STABILIZATION_H
#define LEKA_MOTI_STABILIZATION_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"

void stabilizationTask() {
	Serial.println(F("Wow! Stabilizing!"));
	heart.fade(200, RED_PURE, BLUE_PURE);
	heart.fade(200, BLUE_PURE, GREEN_PURE);
	heart.fade(200, GREEN_PURE, RED_PURE);
	heart.turnOff();

}

static msg_t StabilizationThread(void *arg) {
	(void)arg;

	StabilizationThd = chThdSelf();

	while(TRUE) {
		if (sleeping == TRUE) {
			stabilizationTask();
		}
		else {
			//do nothing
		}
	}
}

#endif // LEKA_MOTI_STABILIZATION_H