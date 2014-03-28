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
#include "Tools.h"

#include "Led.h"
#include "Sensors.h"

Led heart = Led(11, 12, 13);
Sensors sensors;

int16_t mapYaw, mapPitch, mapRoll;
SEMAPHORE_DECL(output, 0);

static WORKING_AREA(waLedThread, 260);
static WORKING_AREA(waSensorsThread, 260);

static msg_t LedThread(void *arg) {

	(void) arg;

	while (TRUE) {
		mapYaw = map(sensors.getYPR(0), -180, 180, 0, 255);
		mapPitch = map(sensors.getYPR(1), -90, 90, 0, 255);
		mapRoll = map(sensors.getYPR(2), -90, 90, 0, 255);
		heart.shine(mapYaw, mapPitch, mapRoll);
		chThdSleepMilliseconds(100);
	}
	return 0;
}

static msg_t SensorsThread(void *arg) {

	(void) arg;

	while (TRUE) {
		sensors.read();
		sensors.debug();
		chThdSleepMilliseconds(100);
	}
	return 0;
}

void chSetup() {

	serial.println("Starting");

	delay(5000);

	chThdCreateStatic(waLedThread, sizeof(waLedThread),
		NORMALPRIO, LedThread, NULL);
	chThdCreateStatic(waSensorsThread, sizeof(waSensorsThread),
		NORMALPRIO, SensorsThread, NULL);
}


void setup() {

	serial.begin(115200);

	sensors.init();

	delay(500);

	serial.println("Starting");

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

