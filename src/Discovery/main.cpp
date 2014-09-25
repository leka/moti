#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"

#include "Stabilization.h"
#include "Heart.h"
#include "Wander.h"

void mainThread() {

	Serial.println(F("Starting..."));

	Sensors::init();
	Moti::init();
	Light::init();

	Stabilization::init();
	Heart::init();
	Wander::init();

	Moti::start();
	Light::start();
	Heart::start();
	Wander::start();

	while (TRUE) {

		waitMs(1000);

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
