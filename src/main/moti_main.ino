
#define serial Serial

#include <Arduino.h>
#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Serial.h"

// Include all the classes needed to beautifully develop your robot.
// #include "Behaviors.h"
#include "Sensors.h"
// #include "Led.h"
// #include "Motor.h"
// #include "Memory.h"
// #include <Moti.h>

// Then create instances of every class needed
Sensors sensors;
// Motors motors;
// Moti moti;
// Behaviors behave;

void setup() {
	// behave.init();
	sensors.init();
}

void loop() {
	// behave.router();
	// behave.server();
	sensors.read();
	sensors.sendJson();


}
