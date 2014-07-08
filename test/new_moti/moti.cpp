#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Motor.h"
#include "Sensors.h"
// #include "Vector.h"


void chSetup() {
	Serial.println("Starting...");
	
	/*
	Light::fade(HEART, Color(255, 195, 170), Color(254, 0, 0), 1500);
	DriveSystem::go(FORWARD, 180, 500);

	bool drive = false, light = false;

	while (TRUE) {
		if ((DriveSystem::getState() == NONE) && !drive) {
			DriveSystem::stop();
			drive = true;
		}

		if ((Light::getState(HEART) == INACTIVE) && !light) {
			Light::turnOff(HEART);
			light = true;
		}

		if (light && drive)
			break;
	}
	*/

	while (TRUE) {
		Serial.println(Sensors::getGyrY());
	 	waitMs(200);
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	Wire.begin();
	delay(500);

	chBegin(chSetup);

	while(1);
}

void loop() { }

/*

// Example to demonstrate thread definition, semaphores, and thread sleep.
#include "ChibiOS_AVR.h"
#include <Arduino.h>

// The LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);
//------------------------------------------------------------------------------
// Thread 1, turn the LED off when signalled by thread 2.

// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread1, 64);

static msg_t Thread1(void *arg) {

	while (!chThdShouldTerminate()) {
	// Wait for signal from thread 2.
	chSemWait(&sem);

	// Turn LED off.
	digitalWrite(LED_PIN, LOW);
	}
	return 0;
}
//------------------------------------------------------------------------------
// Thread 2, turn the LED on and signal thread 1 to turn the LED off.

// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread2, 64);

static msg_t Thread2(void *arg) {
	pinMode(LED_PIN, OUTPUT);
	while (1) {
	digitalWrite(LED_PIN, HIGH);

	// Sleep for 200 milliseconds.
	chThdSleepMilliseconds(200);

	// Signal thread 1 to turn LED off.
	chSemSignal(&sem);

	// Sleep for 200 milliseconds.
	chThdSleepMilliseconds(200);
	}
	return 0;  
}

// main thread runs at NORMALPRIO
void chSetup() {

	// start blink thread
	chThdCreateStatic(waThread1, sizeof(waThread1),
	NORMALPRIO + 2, Thread1, NULL);

	chThdCreateStatic(waThread2, sizeof(waThread2),
	NORMALPRIO + 1, Thread2, NULL);

}

//------------------------------------------------------------------------------
void setup() {

	chBegin(chSetup);
	// chBegin never returns, main thread continues with mainThread()
	while(1) {
	}
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void loop() {
	// not used
}

*/
