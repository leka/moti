#ifndef LEKA_MOTI_TASKS_H
#define LEKA_MOTI_TASKS_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Led.h"
#include "Sensors.h"


void cruiseTask() {
	Serial.println(F("Cruising..."));
	chThdSleepMilliseconds(4000);

	Serial.println(F("Still Cruising..."));
	chThdSleepMilliseconds(4000);

	Serial.println(F("Always Cruising..."));
	chThdSleepMilliseconds(4000);
}

void bumpTask() {
	Serial.println(F("Oups! Bump!"));
	delay(1000);

	Serial.println(F("Going Backward"));
	delay(2000);

	Serial.println(F("Turning Around"));
	delay(1000);

	Serial.println(F("Let's Get Going!"));
}

void stabilizationTask() {
	Serial.println(F("Wow! Stabilizing!"));
	chThdSleepMilliseconds(4000);
}


#endif // LEKA_MOTI_TASKS_H