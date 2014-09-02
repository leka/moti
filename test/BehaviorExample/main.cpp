#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"
#include "Communication.h"
#include "Serial.h"

#include "Stabilization.h"
#include "MyFirstLib.h"

MyFirstClass myFirstObject;

void mainThread() {

	// Init part
	Wire.begin();
	delay(500);
	myFirstObject.methodNumberTwo();

	Sensors::init();
	DriveSystem::start();
	Motion::start();
	Moti::start();
	Light::start();

	// Init our new behavior
	Stabilization::start();

	// Set variables
	bool stabilize = false;

	while (TRUE) {
		if (Moti::isShaken()) {
			if (!stabilize)
				Stabilization::run();
			else
				Stabilization::stop();

			stabilize = !stabilize;
		}

		waitMs(50);
	}
}

void setup() {

	chBegin(mainThread);

	while(1);
}

void loop() {
	// nothing to do here
}
