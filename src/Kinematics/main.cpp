#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"
#include "Motion.h"
#include "Moti.h"
#include "Light.h"

#include "Heart.h"
#include "Wander.h"

#define btserial Serial1

enum MovementState {
	MOVING,
	SPINNING
};

void mainThread() {

	Serial.println(F("Starting initialisation..."));

	Sensors::init();
	Moti::init();
	Light::init();
	Motion::init();

	Heart::init();
	Wander::init();

	Sensors::start();
	Moti::start();

	Light::start();
	Heart::start();

	waitMs(5000);

	Wander::start();

	Serial.println(F("Let's go!"));

	while (TRUE) {

		btserial.print(millis());
		btserial.print("\t");

		btserial.print(DriveSystem::getRightMotorSpeed());
		btserial.print("\t");

		btserial.print(DriveSystem::getRightMotorDirection());
		btserial.print("\t");

		btserial.print(DriveSystem::getLeftMotorSpeed());
		btserial.print("\t");

		btserial.print(DriveSystem::getRightMotorDirection());
		btserial.print("\t");

		btserial.print(Sensors::getEulerPsi());
		btserial.print("\t");

		btserial.print(Sensors::getEulerTheta());
		btserial.print("\t");

		btserial.print(Sensors::getEulerPhi());
		btserial.print("\t");

		btserial.println();

		waitMs(50);
	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	Serial1.begin(115200);
	while (!Serial);

	// Serial1.begin(115200);
	// while (!Serial1);

	Wire.begin();
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
