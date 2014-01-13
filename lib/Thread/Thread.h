#ifndef LEKA_MOTI_ARDUINO_THREAD_H_
#define LEKA_MOTI_ARDUINO_THREAD_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Sensors.h"
#include "Led.h"

// Sensors
Sensors sensors;

// Led
Led heart = Led(11, 12, 13);
Led sleep = Led(8, 9, 10);

// WORKING AREA

// FUNCTIONS
// void chSetup();
//


SEMAPHORE_DECL(SensorSem, 0);

static WORKING_AREA(waHeartThread, 260);
static WORKING_AREA(waSleepThread, 260);
static WORKING_AREA(waAnalyzerThread, 260);
static WORKING_AREA(waSensorThread, 260);


static msg_t SleepThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 0; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 35;     // must multiply by ten in heart.shine();
	volatile uint8_t R = 250;

	while (TRUE) {

		sleep.fade(1300, 0, 0, 0, 0, basePwm, R);

		sleep.fade(650, 0, 0, 0, 0, R, basePwm);

		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

static msg_t SensorThread(void *arg) {
	(void)arg;

	systime_t time = chTimeNow();

	while (TRUE) {
		time += MS2ST(100);
		sensors.read();
		chSemSignal(&SensorSem);
		chThdSleepUntil(time);
	}
	return 0;
}

static msg_t HeartThread(void *arg) {

	(void)arg;

	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
	volatile uint8_t bpm = 15;     // must multiply by ten in heart.shine();
	volatile uint8_t P = 70;
	volatile uint8_t Q = 0;
	volatile uint8_t R = 150;

	while (TRUE) {
		heart.fade(40, basePwm, P, 0, 0, 0, 0);
		heart.fade(40, P, basePwm, 0, 0, 0, 0);

		heart.shine(basePwm, 0, 0);
		chThdSleepMilliseconds(80);

		heart.fade(60, Q, R, 0, 0, 0, 0);
		heart.fade(70, R, basePwm, 0, 0, 0, 0);

		chThdSleepMilliseconds(30000/ bpm);
	}
	return 0;
}

static msg_t AnalyzerThread(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&SensorSem);
		if (sensors.getXYZ(0) > 300) {
			serial.println("ça marche!");
		}
	}
}

void chSetup() {
	chThdCreateStatic(waSleepThread, sizeof(waSleepThread),
		NORMALPRIO, SleepThread, NULL);

	chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
		NORMALPRIO, HeartThread, NULL);

	chThdCreateStatic(waSensorThread, sizeof(waSensorThread),
		NORMALPRIO, SensorThread, NULL);

	chThdCreateStatic(waAnalyzerThread, sizeof(waAnalyzerThread),
		NORMALPRIO, AnalyzerThread, NULL);
}


#endif