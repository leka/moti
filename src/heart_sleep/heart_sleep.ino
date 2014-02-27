#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "Led.h"

Led sleep = Led(8, 9, 10);
Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 15;     // must multiply by ten in heart.shine();
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 150;

	while (TRUE) {
		heart.fade(40, basePwm, P, 0, 0, 0, 0);
		heart.fade(40, P, basePwm, 0, 0, 0, 0);

		heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(80);

		heart.fade(60, Q, R, 0, 0, 0, 0);
		heart.fade(70, R, basePwm, 0, 0, 0, 0);

		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

static WORKING_AREA(waSleepThread, 1000);

static msg_t SleepThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 0; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
	volatile uint8_t R = 250;

	while (TRUE) {

		serial.println("Up");
		sleep.fade(1300, 0, 0, 0, 0, basePwm, R);

		serial.println("Down");
		sleep.fade(650, 0, 0, 0, 0, R, basePwm);

		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

void chSetup() {
	chThdCreateStatic(waSleepThread, sizeof(waSleepThread),
		NORMALPRIO, SleepThread, NULL);
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
