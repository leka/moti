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
#include "Led.h"

Sensors sensors;
Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10;
	volatile uint8_t bpm = 30;
	volatile uint8_t P = 80;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 255;
	volatile uint32_t waitDelay = 0;
	volatile uint8_t i = 0;

	while (TRUE) {
		for (i = basePwm; i < P; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 40000 / (P - basePwm);
			delayMicroseconds(waitDelay);
		}

		for (i = P; i > basePwm; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 40000 / (P - basePwm);
			delayMicroseconds(waitDelay);
		}

		chThdSleepMilliseconds(60);

		for (i = basePwm; i > Q; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 20000 / (basePwm - Q);
			delayMicroseconds(waitDelay);
		}

		for (i = Q; i < R; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 30000 / (R - Q);
			delayMicroseconds(waitDelay);
		}

		for (i = R; i > Q; i--) {
			heart.shine(i, 0, 0);
			waitDelay = 80000 / (R - Q);
			delayMicroseconds(waitDelay);
		}

		for (i = Q; i < basePwm; i++) {
			heart.shine(i, 0, 0);
			waitDelay = 20000 / (basePwm - Q);
			delayMicroseconds(waitDelay);
		}

		// heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

SEMAPHORE_DECL(sens, 0);

static WORKING_AREA(waSensorsThread, 260);

static msg_t SensorsThread(void *arg) {
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

static WORKING_AREA(waOutputThread, 260);

static msg_t OutputThread(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&sens);
		sensors.sendJson();
	}
	return 0;
}


void chSetup() {

	chThdCreateStatic(waSensorsThread, sizeof(waSensorsThread),
		NORMALPRIO, SensorsThread, NULL);

	chThdCreateStatic(waOutputThread, sizeof(waOutputThread),
		NORMALPRIO, OutputThread, NULL);

	chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
		NORMALPRIO, HeartThread, NULL);
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

