//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#define serial Serial
#define debug true

#include <Arduino.h>
#include <Wire.h>

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Serial.h"

// Include all the classes needed to beautifully develop your robot.
#include "Behaviors.h"
#include "Sensors.h"
#include "Led.h"
#include "Motors.h"
#include "Memory.h"
#include "Debug.h"
// #include <Moti.h>

// Then create instances of every classes
Sensors sensors;
Motors motors;
// Moti moti;

Behaviors behave;

int time;
unsigned long previousMillis = 0;
bool out = false;


void setup() {
	behave.init();
	sensors.init();
}

void loop() {
	behave.router();
	behave.server();
	sensors.read();
	sensors.sendJson();


}
