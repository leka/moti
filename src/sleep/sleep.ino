#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Serial.h"

#include "Led.h"

Led sleep = Led(11, 12, 13);

static WORKING_AREA(waSleepThread, 1000);

static msg_t SleepThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 40;     // must multiply by ten in heart.shine();
	volatile uint8_t R = 200;
	// volatile uint16_t waitDelay = 0;
	// volatile uint8_t i = 0;

	while (TRUE) {

		serial.println("Up");
		sleep.fade(1500, 0, 0, 0, 0, basePwm, R);

		// sleep.shine(0, 0, R);
		// chThdSleepMilliseconds(200);
		serial.println("Down");
		sleep.fade(800, 0, 0, 0, 0, R, basePwm);

		// sleep.shine(0, 0, basePwm);
		// heart.fade(40, RAND, RAND);

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
