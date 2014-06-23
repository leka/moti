#define serial Serial

#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"

#include "Sensors.h"
#include "Led.h"
#include "DriveSystem.h"
#include "Motor.h"

DriveSystem drive;
Led light = Led(11, 12, 13);

static WORKING_AREA(waThread1, 1024);

static msg_t Thread1 (void *arg) {

	(void)arg;

	while (TRUE) {

		drive.go();
		chThdSleepMilliseconds(3000);
		drive.stop();
		chThdSleepMilliseconds(2500);
		drive.turn(RIGHT);
		chThdSleepMilliseconds(1500);
		drive.stop();
		chThdSleepMilliseconds(3000);

		drive.go();
		chThdSleepMilliseconds(3000);
		drive.stop();
		chThdSleepMilliseconds(2500);
		drive.turn(LEFT);
		chThdSleepMilliseconds(1500);
		drive.stop();
		chThdSleepMilliseconds(3000);
	}
	return 0;
}

static WORKING_AREA(waThread2, 1024);

static msg_t Thread2 (void *arg) {

	(void)arg;

	while (TRUE) {
		light.fade(500, RAND, RAND);
	}

	return 0;
}

void chSetup() {

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);

	chThdCreateStatic(waThread2, sizeof(waThread2),
		NORMALPRIO, Thread2, NULL);

}


void setup() {

	serial.begin(115200);

	delay(5000);

	serial.println("Starting...");

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

