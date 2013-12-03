#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Serial.h"

#include "Sensors.h"

Sensors sensors;

static WORKING_AREA(waThread1, 260);

static msg_t Thread1(void *arg) {

	while (TRUE) {
		sensors.read();
		chThdSleepMilliseconds(33);

	}
	return 0;
}

static WORKING_AREA(waThread2, 260);

static msg_t Thread2(void *arg) {

	while (TRUE) {
		sensors.sendJson();
		chThdSleepMilliseconds(200);
	}
	return 0;
}


void chSetup() {


	serial.println("Starting");

	delay(500);

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);

	chThdCreateStatic(waThread2, sizeof(waThread2),
		NORMALPRIO, Thread2, NULL);

}


void setup() {

	serial.begin(115200);

	sensors.init();


	delay(1000);


	// sensors.read();
	// sensors.sendJson();

	// delay(500);

	// sensors.read();
	// sensors.sendJson();

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

