#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Moti.h"
#include "Sensors.h"
#include "Motion.h"
#include "DriveSystem.h"

void mainThread() {

	//INITIALIZATION
	Moti::init();
	Moti::start();

	while (TRUE) {

			DriveSystem::go(FORWARD, 255);
			Serial.println	("starting");

		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	while (!Serial);

	// Serial1.begin(115200);
	// while (!Serial1);

	Wire.begin();
	delay(5000);

	chBegin(mainThread);

	while(1);

	return 0;
}