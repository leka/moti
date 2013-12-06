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

SEMAPHORE_DECL(sens, 0);

static WORKING_AREA(waThread1, 260);

static msg_t Thread1(void *arg) {
	(void)arg;

	systime_t time = chTimeNow();

	while (TRUE) {
		time += MS2ST(50);
		sensors.read();
		chSemSignal(&sens);
		chThdSleepUntil(time);
		serial.print("BTime : ");
		serial.println(chTimeNow() - time);
	}
	return 0;
}

static WORKING_AREA(waThread2, 260);

static msg_t Thread2(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&sens);
		sensors.sendJson();
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

	sensors.init();

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

