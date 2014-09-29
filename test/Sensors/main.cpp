#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"
#include "Heart.h"

void chSetup() {

	Sensors::init();
	Sensors::start();

	// Light::init();
	// Light::start();

	// Heart::init();
	// Heart::start();

	while (TRUE) {
		Serial.print(F("Time: "));
		Serial.print(millis());

		Serial.print(F("  X: "));
		Serial.print(Sensors::getAccX());
		Serial.print(F("  Y: "));
		Serial.print(Sensors::getAccY());
		Serial.print(F("  Z: "));
		Serial.print(Sensors::getAccZ());

		Serial.print(F("  Yaw: "));
		Serial.print(Sensors::getGyrY());
		Serial.print(F("  Pitch: "));
		Serial.print(Sensors::getGyrP());
		Serial.print(F("  Roll: "));
		Serial.print(Sensors::getGyrR());

		Serial.print(F("  Yaw: "));
		Serial.print(Sensors::getGyrYDeg());
		Serial.print(F("  Pitch: "));
		Serial.print(Sensors::getGyrPDeg());
		Serial.print(F("  Roll: "));
		Serial.print(Sensors::getGyrRDeg());

		Serial.print(F("  Phi: "));
		Serial.print(Sensors::getEulerPhi());
		Serial.print(F("  Theta: "));
		Serial.print(Sensors::getEulerTheta());
		Serial.print(F("  Psi: "));
		Serial.print(Sensors::getEulerPsi());

		Serial.println();

		waitMs(25);
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	Wire.begin();
	delay(500);

	chBegin(chSetup);

	while (TRUE);
}

void loop() { }
