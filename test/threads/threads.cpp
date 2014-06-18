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

#include "Thread.h"
#include "Setup.h"

void setup() {
	serial.begin(115200);
	sensors.init();

	serial.println("System starting....\n");
	delay(3000);

	chBegin(chSetup);

	while(1) {
		// nothing to do here
	}
}

void loop() {
	// nothing to do here
}
