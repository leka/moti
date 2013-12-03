#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Motor.h"
#include "Serial.h"

Motor right_motor = Motor(7,6);
Motor left_motor = Motor(4,5);


static WORKING_AREA(waThread1, 1024);

static msg_t Thread1(void *arg) {

	while (TRUE) {

		serial.print(F("Unused Stack: "));
		serial.println(chUnusedStack(waThread1, sizeof(waThread1)));

		serial.println("Right Motor");
		right_motor.spin(0);
		chThdSleepMilliseconds(2000);
		right_motor.spin(0, 100);
		chThdSleepMilliseconds(2000);

		right_motor.stop();
		chThdSleepMilliseconds(2000);

		right_motor.spin(1);
		chThdSleepMilliseconds(2000);
		right_motor.spin(1, 100);
		chThdSleepMilliseconds(2000);

		right_motor.stop();
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

	serial.println("Starting...");

	chBegin(chSetup);

	while(1) {
	}
}

void loop() {

}

