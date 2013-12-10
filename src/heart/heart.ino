#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"

#include "Led.h"

Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 30;     // must multiply by ten in heart.shine();
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 255;
	// volatile uint16_t waitDelay = 0;
	// volatile uint8_t i = 0;

	while (TRUE) {
		heart.fade(50, basePwm, P, 0, 0, 0, 0);
		heart.fade(50, P, basePwm, 0, 0, 0, 0);

		heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(80);

		// heart.fade(20, basePwm, Q, 0, 0, 0, 0);
		heart.fade(60, Q, R, 0, 0, 0, 0);
		heart.fade(100, R, Q, 0, 0, 0, 0);
		// heart.fade(20, Q, basePwm, 0, 0, 0, 0);

		// heart.fade(40, RAND, RAND);
		heart.shine(basePwm, 0, 0);

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
