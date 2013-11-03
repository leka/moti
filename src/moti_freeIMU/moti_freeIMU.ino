#include <Arduino.h>
#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Serial.h"

// Include all the classes needed to beautifully develop your robot.
#include <Sensors.h>

// Then create instances of every classes
Sensors sensors;

int time;
unsigned long previousMillis = 0;
bool out = false;


void setup() {
	// moti.initDebug(sensors, motors);
	Serial.begin(115200);
	sensors.open();

}

void loop() {

	sensors.read();
	sensors.sendJson();

delay(200);

}
