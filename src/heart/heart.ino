#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"

#include "Led.h"

Led heart = Led(11, 12, 13);

static WORKING_AREA(waLedThread, 1000);

static msg_t LedThread(void *arg) {

	(void)arg;

	volatile uint16_t basePwm = 0;
	volatile uint16_t bpm = 60;
	volatile uint16_t currentPwm = 0;
	volatile uint16_t P = 70;
	volatile uint16_t Q = 0;
	volatile uint16_t R = 170;
	volatile uint32_t waitDelay = 0;
	volatile int32_t slice = 0;
	volatile uint16_t i = 0;

	while (TRUE) {
		// for (i = basePwm; i < P; i++) {
		// 	currentPwm = basePwm + 20 * sin(0.041 * i);
		// 	heart.shine(currentPwm, 0, 0);
		// 	chThdSleepMilliseconds(80/(P-basePwm));
		// }

		for (i = basePwm; i < P; i++) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P - basePwm;
			waitDelay = 40000 / abs(slice);
			serial.println(slice);
			delayMicroseconds(waitDelay);
		}

		for (i = P; i > basePwm; i--) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P-basePwm;
			waitDelay = 40000 / abs(slice);
			serial.println(waitDelay);
			delayMicroseconds(waitDelay);
		}

		delayMicroseconds(60000);

		for (i = basePwm; i > Q; i--) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P-basePwm;
			waitDelay = 20000 / abs(slice);
			serial.println(waitDelay);
			delayMicroseconds(waitDelay);
		}

		for (i = Q; i < R; i++) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P-basePwm;
			waitDelay = 10000 / abs(slice);
			serial.println(waitDelay);
			delayMicroseconds(waitDelay);
		}

		for (i = R; i > Q; i--) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P-basePwm;
			waitDelay = 12500 / abs(slice);
			serial.println(waitDelay);
			delayMicroseconds(waitDelay);
		}

		for (i = Q; i < basePwm; i++) {
			currentPwm = i;
			heart.shine(currentPwm, 0, 0);
			slice = P-basePwm;
			waitDelay = 20000 / abs(slice);
			serial.println(waitDelay);
			delayMicroseconds(waitDelay);
		}

		delayMicroseconds(6000 / bpm);

		heart.shine(basePwm, 0, 0);

		delay(800);

	}
	return 0;
}

void chSetup() {
	chThdCreateStatic(waLedThread, sizeof(waLedThread),
		NORMALPRIO, LedThread, NULL);
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
