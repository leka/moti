#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"
#include "Motion.h"
#include "Moti.h"
#include "Light.h"

#include "Stabilization.h"
#include "Heart.h"

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

	Sensors::start();
	Moti::start();
	Light::start();

	Heart::start();
	Stabilization::start();

	while (TRUE) {

		waitMs(5000);

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
