#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"

#include "Led.h"

Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 1; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 3;     // must multiply by ten in heart.shine();
	volatile uint8_t P = 8;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 25;
	volatile uint32_t waitDelay = 0;
	volatile uint8_t i = 0;

	while (TRUE) {
		for (i = basePwm; i < P; i++) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 40000 / (P - basePwm);
			chThdSleepMicroseconds(waitDelay);
		}

		for (i = P; i > basePwm; i--) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 40000 / (P - basePwm);
			chThdSleepMicroseconds(waitDelay);
		}

		chThdSleepMilliseconds(60);

		for (i = basePwm; i > Q; i--) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 20000 / (basePwm - Q);
			chThdSleepMicroseconds(waitDelay);
		}

		for (i = Q; i < R; i++) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 30000 / (R - Q);
			chThdSleepMicroseconds(waitDelay);
		}

		for (i = R; i > Q; i--) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 80000 / (R - Q);
			chThdSleepMicroseconds(waitDelay);
		}

		for (i = Q; i < basePwm; i++) {
			heart.shine(i * 10, 0, 0);
			waitDelay = 20000 / (basePwm - Q);
			chThdSleepMicroseconds(waitDelay);
		}

		// heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

void chSetup() {
	chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
		NORMALPRIO, HeartThread, NULL);
}


void setup() {
	serial.begin(115200);
	chBegin(chSetup);
	while(1) {
	}
}

void loop() {
	// nothing to do here
}
