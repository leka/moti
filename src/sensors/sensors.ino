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

static WORKING_AREA(waThread1, 1024);

static msg_t Thread1(void *arg) {

	while (TRUE) {

		serial.print(F("Unused Stack: "));
		serial.println(chUnusedStack(waThread1, sizeof(waThread1)));
		serial.println("OK");

		sensors.read();
		sensors.sendJson();

		chThdSleepMilliseconds(500);

	}
	return 0;
}


void chSetup() {

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);

}


void setup() {

	serial.begin(115200);

	delay(1000);

	sensors.init();

	serial.println("Starting");

	delay(500);

	sensors.read();
	sensors.sendJson();

	delay(500);

	sensors.read();
	sensors.sendJson();

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

