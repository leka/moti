#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Motor.h"
#include "Queue.h"
#include "Sensors.h"
#include "Serial.h"

/* #include "Vector.h" */


void chSetup() {
	Serial.println(F("Starting..."));

	float currentAngle = 0.f;

	while (TRUE) {
		// Serial.println(Sensors::getAccX());

		if (Light::getState(HEART) == INACTIVE) {
			Light::fade(HEART, Color::randomColor(), Color::randomColor(), 1500);
		}

		currentAngle = Sensors::getEulerPhi();
		
		if (Sensors::getAccX() > 80) {
			Serial.println(F("BACKWARD"));
			DriveSystem::go(BACKWARD, 200, 0);
		}
		else if (Sensors::getAccX() < -80) {
			Serial.println(F("FORWARD"));
			DriveSystem::go(FORWARD, 200, 0);
		}
		else if (Sensors::getAccY() > 80) {
			Serial.println(F("SPIN RIGHT"));
			DriveSystem::spin(RIGHT, 200, 1.57f);
		}
		else if (Sensors::getAccY() < -80) {
			Serial.println(F("SPIN LEFT"));
			DriveSystem::spin(LEFT, 200, 1.57f);
		}
		else if (abs(currentAngle) > 0.34f) {
			Serial.println(F("FACING"));
			DriveSystem::spin(currentAngle > 0.0f ? LEFT : RIGHT, 180, abs(currentAngle));
		}
		else if (DriveSystem::getState() != NONE) {
				DriveSystem::stop();
		}

		waitMs(50);
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	Wire.begin();
	delay(500);

	chBegin(chSetup);

	while(1);
}

void loop() { }
