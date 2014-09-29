#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"

void chSetup() {

	Sensors::init();
	Sensors::start();

	Serial.println(1);
	while (TRUE) {
		Serial.print("Time: ");
		Serial.println(millis());

		Serial.print("  X: ");
		Serial.print(Sensors::getAccX());
		Serial.print("  Y: ");
		Serial.print(Sensors::getAccY());
		Serial.print("  Z: ");
		Serial.print(Sensors::getAccZ());

		Serial.print("  Yaw: ");
		Serial.print(Sensors::getGyrY());
		Serial.print("  Pitch: ");
		Serial.print(Sensors::getGyrP());
		Serial.print("  Roll: ");
		Serial.print(Sensors::getGyrR());

		Serial.print("  Yaw: ");
		Serial.print(Sensors::getGyrYDeg());
		Serial.print("  Pitch: ");
		Serial.print(Sensors::getGyrPDeg());
		Serial.print("  Roll: ");
		Serial.print(Sensors::getGyrRDeg());

		Serial.print("  Phi: ");
		Serial.print(Sensors::getEulerPhi());
		Serial.print("  Theta: ");
		Serial.print(Sensors::getEulerTheta());
		Serial.print("  Psi: ");
		Serial.print(Sensors::getEulerPsi());

		Serial.println();

		waitMs(25);
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	Serial.println(0);
	Wire.begin();
	delay(500);

	Serial.println(0);

	chBegin(chSetup);

	while (TRUE);
}

void loop() { }
