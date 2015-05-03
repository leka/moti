#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"
#include "Motion.h"
#include "Moti.h"
#include "Light.h"

#include "Heart.h"
#include "Spinner.h"
#include "Wander.h"

enum MovementState {
	MOVING,
	SPINNING
};

void mainThread() {

	bool hasBeenShaken = false;

	Serial.println(F("Starting initialisation..."));
	Sensors::init();
	Moti::init();
	Light::init();
	Motion::init();

	Heart::init();
	Spinner::init();
	Wander::init();

	Sensors::start();
	Moti::start();

	Light::start();
	Heart::start();
	Wander::start();

	while (TRUE) {

		while (Moti::isShaken()) {
			Serial.println(F("Shaking"));
			hasBeenShaken = true;
			waitMs(50);
		}

		if (hasBeenShaken) {

			Wander::stop();
			Serial.println(F("Spinning"));
			Spinner::start();

			hasBeenShaken = false;
		}

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
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
