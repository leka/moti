#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "FreeIMU.h"
#include "Moti.h"
#include "Sensors.h"


void chSetup() {
	while (TRUE) {
		Serial.println("Accelerometer:");
		Serial.print("\tX: ");
		Serial.println(Sensors::getAccX());
		Serial.print("\tY: ");
		Serial.println(Sensors::getAccY());
		Serial.print("\tZ: ");
		Serial.println(Sensors::getAccZ());

		Serial.println("Gyroscope:");
		Serial.print("\tYaw: ");
		Serial.println(Sensors::getGyrY());
		Serial.print("\tPitch: ");
		Serial.println(Sensors::getGyrP());
		Serial.print("\tRoll: ");
		Serial.println(Sensors::getGyrR());

		Serial.print("\tPhi: ");
		Serial.println(Sensors::getEulerPhi());
		Serial.print("\tTheta: ");
		Serial.println(Sensors::getEulerTheta());
		Serial.print("\tPsi: ");
		Serial.println(Sensors::getEulerPsi());

		Serial.print("Is Falling? ");
		Serial.println(Sensors::isFalling());

		Serial.print("Is Inactive? ");
		Serial.println(Sensors::isInactive());

		Serial.println();

		waitMs(1000);
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
