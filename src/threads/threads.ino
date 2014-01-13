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

void setup() {
	serial.begin(115200);
	sensors.init();

	for (int i = 5; i >= 0; --i)
	{
		serial.println(i);
		delay(1000);
	}

	chBegin(chSetup);
	while(1) {
	}
}

void loop() {
	// nothing to do here
}
