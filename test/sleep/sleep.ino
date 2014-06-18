#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "Led.h"

Led sleep = Led(11, 12, 13);

static WORKING_AREA(waSleepThread, 1000);

static msg_t SleepThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 5; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
	volatile uint8_t R = 255;

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
