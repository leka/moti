#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"

#include "Stabilization.h"
#include "Heart.h"
#include "Wander.h"

enum MovementState {
	SLEEPING,
	STABILIZING
};

void mainThread() {

	bool hasBeenShaken = false;
	MovementState _actionState = SLEEPING;

	Serial.println(F("Starting..."));

	Sensors::init();
	Moti::init();
	Light::init();

	Stabilization::init();
	Heart::init();
	Wander::init();

	Sensors::start();
	Moti::start();
	Light::start();

	Heart::start();
	Stabilization::start();

	while (TRUE) {

		while (Moti::isShaken()) {
			hasBeenShaken = true;
			waitMs(50);
		}

		if (hasBeenShaken) {

			if (_actionState == SLEEPING) {
				Serial.println(1);
				_actionState = STABILIZING;
				Stabilization::start();
				Wander::stop();
			}
			else {
				Serial.println(2);
				_actionState = SLEEPING;
				Stabilization::stop();
				Wander::start();
			}

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
