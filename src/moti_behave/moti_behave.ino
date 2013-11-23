
#define serial Serial
#define debug true

#include <Arduino.h>
#include <Wire.h>

#include "CommunicationUtils.hpp"
#include "DebugUtils.hpp"
#include "ADXL345.hpp"
#include "ITG3200.hpp"
#include "FreeIMU.hpp"
#include "Serial.hpp"

// Include all the classes needed to beautifully develop your robot.
#include "Behaviors.hpp"
#include "Sensors.hpp"
#include "Led.hpp"
#include "Motor.hpp"
#include "Memory.hpp"
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
