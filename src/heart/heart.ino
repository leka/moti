#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"

#include "Led.h"

Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10;
	volatile uint8_t bpm = 30;
	volatile uint8_t P = 80;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 255;
	volatile uint32_t waitDelay = 0;
	volatile uint8_t i = 0;
	volatile uint8_t j = 0;

	while (TRUE) {
		for (i = basePwm; i < P; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 4000 / (P - basePwm);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
		}

		for (i = P; i > basePwm; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 4000 / (P - basePwm);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
		}

		chThdSleepMilliseconds(60);

		for (i = basePwm; i > Q; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 2000 / (basePwm - Q);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
		}

		for (i = Q; i < R; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 3000 / (R - Q);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
		}

		for (i = R; i > Q; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 8000 / (R - Q);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
		}

		for (i = Q; i < basePwm; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 2000 / (basePwm - Q);
			// delayMicroseconds(waitDelay);
			for (j = 0; j < waitDelay ; j++){}
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
