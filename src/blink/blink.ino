// Example to demonstrate thread definition, semaphores, and thread sleep.
#include <Arduino.h>
#include <ChibiOS_AVR.h>

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

		Serial.println("Thread1");
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
		Serial.println("Thread2");

		digitalWrite(LED_PIN, HIGH);

		// Sleep for 200 milliseconds.
		chThdSleepMilliseconds(100);

		// Signal thread 1 to turn LED off.
		chSemSignal(&sem);

		chThdSleepMilliseconds(100);

		digitalWrite(LED_PIN, HIGH);

		// Sleep for 200 milliseconds.
		chThdSleepMilliseconds(100);

		// Signal thread 1 to turn LED off.
		chSemSignal(&sem);

		chThdSleepMilliseconds(100);

		digitalWrite(LED_PIN, HIGH);

		// Sleep for 200 milliseconds.
		chThdSleepMilliseconds(100);

		// Signal thread 1 to turn LED off.
		chSemSignal(&sem);

		// Sleep for 200 milliseconds.
		chThdSleepMilliseconds(800);
	}
	return 0;
}

static WORKING_AREA(waThread3, 64);

static msg_t Thread3(void *arg) {

	while (TRUE) {
		Serial.println("Hello World!");
		chThdSleepMilliseconds(500);
	}
	return 0;
}

void chSetup() {

	// start blink thread
	chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO + 2, Thread1, NULL);

	chThdCreateStatic(waThread2, sizeof(waThread2),
		NORMALPRIO + 1, Thread2, NULL);

	chThdCreateStatic(waThread3, sizeof(waThread3),
		NORMALPRIO + 1, Thread3, NULL);

}
//------------------------------------------------------------------------------
void setup() {

	Serial.begin(115200);

	chBegin(chSetup);
	// chBegin never returns, main thread continues with mainThread()
	while(1) {
	}
}
//------------------------------------------------------------------------------
// main thread runs at NORMALPRIO

//------------------------------------------------------------------------------
void loop() {
	// not used
}

