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
		sensors.sendJson();

		chThdSleepMilliseconds(100);
	}
	return 0;
}


void chSetup() {

	sensors.init();

	serial.println("Starting");

	delay(500);

	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO, Thread1, NULL);

}


void setup() {

	 char stkVar;
  extern char* __malloc_heap_end;
  // allow 256 locations for loop() stack
  __malloc_heap_end = &stkVar - 256;

	serial.begin(115200);

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

