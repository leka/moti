#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Led.h"

static WORKING_AREA(waThread1, 260);

static msg_t Thread1(void *arg) {

	while (TRUE) {


	}
	return 0;
}

void chSetup() {

	serial.println("Starting");

	delay(500);

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);



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

