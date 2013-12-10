#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Serial.h"

#include "Led.h"

Led heart = Led(11, 12, 13);

SEMAPHORE_DECL(output, 0);

static WORKING_AREA(waLedThread, 260);
static WORKING_AREA(waSerialThread, 260);

static msg_t LedThread(void *arg) {

	(void) arg;

	while (TRUE) {

		heart.fade(1200, 50, 0, 100, 0, 150, 0);

		chThdSleepMilliseconds(2000);

	}
	return 0;
}

static msg_t SerialThread(void *arg) {

	while (TRUE) {
		// chSemWait(&output);
		// serial.print("red : ");
		// serial.println(heart.getRgb(0));
		// serial.print("green : ");
		// serial.println(heart.getRgb(1));
		// serial.print("blue : ");
		// serial.println(heart.getRgb(2));
		// heart.turnOff();
	}
	return 0;
}

void chSetup() {

	serial.println("Starting");

	delay(500);

	chThdCreateStatic(waLedThread, sizeof(waLedThread),
		NORMALPRIO, LedThread, NULL);
	chThdCreateStatic(waSerialThread, sizeof(waSerialThread),
		NORMALPRIO, SerialThread, NULL);
}


void setup() {

	serial.begin(115200);

	delay(500);

	serial.println("Starting");

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

