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

uint32_t startBumpTime = 0;

#define Z_HISTORY_SIZE 30
float dz[Z_HISTORY_SIZE] = { 0.f };
uint8_t z_index = 0;
float z = 200.f, old_z = 200.f;

// BASIC TASKS
void arbitrerTask() {
	sensors.readAccelerometer();
	// xAverage = (alpha * sensors.getXYZ(0) + (256 - alpha) * xAverage ) / 256;
	Serial.print(F("X: "));
	Serial.println(sensors.getXYZ(0));
	//Serial.println(xAverage);
	// sensors.sendJson();
	// elapsedTime = elapsedTime + chTimeNow() - lastTime;
	// lastTime = chTimeNow();
	// Serial.print(F("Sleeping = "));
	// Serial.println(sleeping);
	// Serial.print(F("Time = "));
	// Serial.println(elapsedTime);

	/****** BUMPING PART ******/
	//
	// if (abs(sensors.getXYZ(0)) >= 165) { //xThreshold) {
	// 	if (startBumpTime == 0)
	// 		startBumpTime = chTimeNow();
	// 	else if (chTimeNow() - startBumpTime > 1000) {
	// 		Serial.println(F("BUMP!"));
	// 		sleeping = FALSE;
	// 		chEvtSignal(BumpThd, bumpEvent);
	// 	}
	// }
	// else
	// 	startBumpTime = 0;
	//
	/**************************/

	/****** STABILIZATION PART ******/

	old_z = z;
	z = sensors.getXYZ(2);

	dz[z_index] = abs(z - old_z);
	z_index = (z_index + 1) % Z_HISTORY_SIZE;

	float sum = 0;
	for (uint8_t i = 0; i < Z_HISTORY_SIZE; ++i)
		sum += dz[i];

	//Serial.print("Sum: ");
	//Serial.println(sum);
	//
	// if (sum > Z_HISTORY_SIZE * 80.f) {
	// 	Serial.println("STAB");
	// 	Serial.println(sleeping);
	//
	// 	z_index = 0;
	// 	for (uint8_t i = 0; i < Z_HISTORY_SIZE; ++i)
	// 		dz[i] = 0.f;
	//
	// 	robot.stop(0);
	//
	// 	if (sleeping) {
	// 		//chEvtGetAndClearEvents(stabilizationEvent);
	// 	}
	// 	else {
	// 		Serial.println("Stabilizing");
	// 		//chEvtSignal(StabilizationThd, stabilizationEvent);
	// 	}
	//
	// 	sleeping = !sleeping;
	// 	chThdSleepMilliseconds(1000);
	// }

	/********************************/


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

	return (msg_t)0;
}


#endif // LEKA_MOTI_ARBITRER_H
