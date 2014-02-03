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
#include "Tools.h"

Sensors sensors;
Led heart = Led(11, 12, 13);

static WORKING_AREA(waHeartThread, 1000);

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

SEMAPHORE_DECL(sens, 0);

static WORKING_AREA(waSensorsThread, 260);

static msg_t SensorsThread(void *arg) {
	(void)arg;

	systime_t time = chTimeNow();

	while (TRUE) {
		time += MS2ST(100);
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
		sensors.debug();
	}
	return 0;
}


void chSetup() {

	chThdCreateStatic(waSensorsThread, sizeof(waSensorsThread),
		NORMALPRIO+2, SensorsThread, NULL);

	chThdCreateStatic(waOutputThread, sizeof(waOutputThread),
		NORMALPRIO+1, OutputThread, NULL);

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

