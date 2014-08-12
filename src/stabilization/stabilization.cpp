#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Environment.h"
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

	Drive::start();
    DriveSystem::start();
    Environment::start();
    Light::start();

	float currentAngle = 0.0f;

	double input = 0.0f;
	double output = 0.0f;


	while (TRUE) {
		/*
		if (Light::getState(HEART) == INACTIVE) {
			Light::fade(HEART, Color::randomColor(), Color::randomColor(), 1500);
		}
		*/

		currentAngle = Sensors::getEulerPhi();

		input = (double)Sensors::getAccX();
		output = -0.75 * input;

		/*Serial.print(input);
		Serial.print(F("  "));
		Serial.println(output);
		*/

		if (abs(output) > 100.0f) {
			DriveSystem::go(output < 0.0f ? BACKWARD : FORWARD, (uint8_t)abs(output), 100);
		}
		else if (Sensors::getAccY() > 80) {
			Serial.println(F("SPIN RIGHT"));
			DriveSystem::spin(RIGHT, 200, 1.57f);
		}
		else if (Sensors::getAccY() < -80) {
			Serial.println(F("SPIN LEFT"));
			DriveSystem::spin(LEFT, 200, 1.57f);
		}
		else if (abs(currentAngle) > 0.45f) {
			Serial.println(F("FACING"));
			DriveSystem::spin(currentAngle > 0.0f ? LEFT : RIGHT, 150, abs(currentAngle));
		}
		else if (DriveSystem::getState() != NONE) {
			DriveSystem::stop(0);
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
