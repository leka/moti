#ifndef LEKA_MOTI_STABILIZATION_H
#define LEKA_MOTI_STABILIZATION_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"

float x, y;
uint32_t stabElapsedTime = 0, stabLastSpin = 0;

void stabilizationTask() {
	Serial.println(F("Wow! Stabilizing!"));
	
	sensors.read();
	x = sensors.getXYZ(0);
	y = sensors.getXYZ(1);

	stabElapsedTime = chTimeNow() - stabLastSpin;

	if ((stabElapsedTime > 350) && (abs(y) > 90) && (abs(y - 20) > abs(x))) {
		robot.spin(sensors, RIGHT, 110, 90);
		stabLastSpin = chTimeNow();
	}

	while (abs(x) > 50) {
		sensors.read();
		x = sensors.getXYZ(0);
		
		Serial.print(x);
		Serial.print(' ');
		Serial.println(y);
		
		Direction dir;

		if (x >= 0)
			dir = BACK;
		else
			dir = FORTH;

		robot.launch(dir, 110, 0);
	}

	float alpha = sensors.getEuler(0);
	Rotation sDir = LEFT;

	if (alpha < 0) {
		alpha *= -1;
		sDir = RIGHT;
	}

	/*
	if (alpha > 25.)
		robot.spin(sensors, sDir, 110, alpha - 25.);
	*/

	robot.stop(0);
}

static msg_t StabilizationThread(void *arg) {
	(void)arg;

	StabilizationThd = chThdSelf();

	while(TRUE) {
		Serial.println(sleeping);

		if (sleeping)
			stabilizationTask();

		chThdSleepMilliseconds(70);
	}

	return (msg_t)0;
}

#endif // LEKA_MOTI_STABILIZATION_H