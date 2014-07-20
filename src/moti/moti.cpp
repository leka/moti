#include <Arduino.h>
#include <Wire.h>

#include "Moti.h"
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Color.h"
#include "Drive.h"
#include "DriveSystem.h"
#include "Environment.h"
#include "FreeIMU.h"
#include "Led.h"
#include "Light.h"
#include "Motor.h"
#include "Queue.h"
#include "Sensors.h"
#include "Serial.h"

#include "lib/Arbitrer/Arbitrer.h"
/*
#include "lib/Cruise/Cruise.h"
#include "lib/Environment/Environment.h"
*/


void chSetup() {
	Serial.println(F("Starting..."));

    delay(5000);

    Drive::start();
    DriveSystem::start();
    Environment::start();
    Light::start();
    Stabilization::start();

	Arbitrer::launch();
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
