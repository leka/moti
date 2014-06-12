#ifndef LEKA_MOTI_ARBITRER_H
#define LEKA_MOTI_ARBITRER_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"

// THRESHOLDS
int16_t xThreshold = 300;
int16_t yThreshold = 300;
int16_t zThreshold = 500;
uint16_t xAverage = 0;
uint8_t alpha = 178;
systime_t timeThreshold = 15000;
systime_t elapsedTime = 0;
systime_t lastTime = 0;

// BASIC TASKS
void arbitrerTask() {
	sensors.readAccelerometer();
	xAverage = (alpha * sensors.getXYZ(0) + (256 - alpha) * xAverage ) / 256;
	Serial.println(xAverage);
	// sensors.sendJson();
	// elapsedTime = elapsedTime + chTimeNow() - lastTime;
	// lastTime = chTimeNow();
	// Serial.print(F("Sleeping = "));
	// Serial.println(sleeping);
	// Serial.print(F("Time = "));
	// Serial.println(elapsedTime);

	if (sensors.getXYZ(0) >= xThreshold) {
		sleeping = FALSE;
		chEvtSignal(BumpThd, bumpEvent);
	}
	// if (sensors.getXYZ(2) >= zThreshold) {
	// 	sleeping = FALSE;
	// 	// Serial.println(F("Calling Cruise Thread"));
	// 	chEvtGetAndClearEvents(stabilizationEvent);
	// 	chEvtSignal(CruiseThd, cruiseEvent);
	// 	elapsedTime = 0;
	// }
	// if (elapsedTime >= timeThreshold || sleeping == TRUE) {
	// 	// Serial.println(F("Calling Stabilization Thread"));
	// 	elapsedTime = 0;
	// 	sleeping = TRUE;
	// 	chEvtGetAndClearEvents(cruiseEvent);
	// 	chEvtSignal(StabilizationThd, stabilizationEvent);
	// }

	chThdSleepMilliseconds(70);
}

static msg_t ArbitrerThread(void *arg) {
	(void)arg;

	ArbitrerThd = chThdSelf();

	while(TRUE) {
		arbitrerTask();
	}
}


#endif // LEKA_MOTI_ARBITRER_H
