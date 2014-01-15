#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Motor.h"
#include "DriveSystem.h"
#include "Serial.h"

DriveSystem drive;

static WORKING_AREA(waThread1, 1024);

static msg_t Thread1(void *arg) {

	(void)arg;

	while (TRUE) {

		serial.println("Forward");
		drive.go(FORTH);
		chThdSleepMilliseconds(2000);
		drive.stop();
		chThdSleepMilliseconds(500);
		serial.println("Backward");
		drive.go(BACK);
		chThdSleepMilliseconds(2000);

		serial.println("Stop");
		drive.stop();
		chThdSleepMilliseconds(2000);

		serial.println("Spin right");
		drive.spin(RIGHT);
		chThdSleepMilliseconds(2000);
		drive.stop();
		chThdSleepMilliseconds(500);
		serial.println("Spin left");
		drive.spin(LEFT);
		chThdSleepMilliseconds(2000);

		serial.println("Stop");
		drive.stop();
		chThdSleepMilliseconds(2000);

	}
	return 0;
}


void chSetup() {

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);

}


void setup() {

	serial.begin(115200);

	delay(3000);

	serial.println("Starting...");

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

