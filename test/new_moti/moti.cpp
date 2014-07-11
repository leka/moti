#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "FreeIMU.h"
//#include "Led.h"
//#include "Light.h"
#include "Motor.h"
#include "Sensors.h"
// #include "Vector.h"


void chSetup() {
	Serial.println("Starting...");
	
	/*
	Light::fade(HEART, Color(255, 195, 170), Color(254, 0, 0), 1500);
	DriveSystem::go(FORWARD, 180, 500);

	bool drive = false, light = false;

	while (TRUE) {
		if ((DriveSystem::getState() == NONE) && !drive) {
			DriveSystem::stop();
			drive = true;
		}

		if ((Light::getState(HEART) == INACTIVE) && !light) {
			Light::turnOff(HEART);
			light = true;
		}

		if (light && drive)
			break;
	}
	*/

	DriveSystem::spin(RIGHT, 150, 1.57f);
	while (DriveSystem::getState() != NONE);

	Serial.println("YOLOL");

	/*
	while (TRUE) {
		Serial.println(Sensors::getEulerPhi());
	 	waitMs(200);
	}
	*/
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
