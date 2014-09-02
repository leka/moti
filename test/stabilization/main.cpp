#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "Color.h"
#include "Motion.h"
#include "Light.h"
#include "Sensors.h"


void chSetup() {
	Serial.println(F("Starting..."));

	DriveSystem::start();
    Motion::start();
    Moti::start();
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
			Motion::go(output < 0.0f ? BACKWARD : FORWARD, (uint8_t)abs(output), 100);
		}
		else if (Sensors::getAccY() > 80) {
			Serial.println(F("SPIN RIGHT"));
			Motion::spin(RIGHT, 200, 1.57f);
		}
		else if (Sensors::getAccY() < -80) {
			Serial.println(F("SPIN LEFT"));
			Motion::spin(LEFT, 200, 1.57f);
		}
		else if (abs(currentAngle) > 0.45f) {
			Serial.println(F("FACING"));
			Motion::spin(currentAngle > 0.0f ? LEFT : RIGHT, 150, abs(currentAngle));
		}
		else if (Motion::getState() != NONE) {
			Motion::stop(0);
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
