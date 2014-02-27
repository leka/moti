#define serial Serial

#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"

#include "Sensors.h"
#include "Led.h"
#include "Motor.h"
#include "DriveSystem.h"

#include "Behaviors.h"
#include "InitThread.h"

void setup() {
	serial.begin(115200);
	sensors.init();

	serial.println("System starting....\n");
	delay(1000);

	chBegin(chSetup);

	while(1) {
		// nothing to do here
	}
}

void loop() {
	// nothing to do here
}
