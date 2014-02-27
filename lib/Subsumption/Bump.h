#ifndef LEKA_MOTI_BUMP_H
#define LEKA_MOTI_BUMP_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Subsumption.h"

void bumpTask() {
	Serial.println(F("Oups! Bump!"));
	robot.stop();
	heart.turnOff();
	delay(2000);
	heart.shine(RED_PURE);

	Serial.println(F("Going Backward"));
	robot.go(BACK);
	delay(2000);
	robot.stop();
	delay(1000);

	Serial.println(F("Turning Around"));
	robot.spin();
	delay(1000);

	Serial.println(F("Let's Get Going!"));
	robot.stop();
	heart.turnOff();
	delay(2000);
	chEvtGetAndClearEvents(bumpEvent);
}

static msg_t BumpThread(void *arg) {
	(void)arg;

	BumpThd = chThdSelf();

	while(TRUE) {
		chEvtWaitAll(bumpEvent);
		bumpTask();
		chEvtGetAndClearEvents(bumpEvent);
	}
}

#endif // LEKA_MOTI_BUMP_H