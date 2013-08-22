//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include <Arduino.h>
#include <Serial.h>
#include <Wire.h>
#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

// Include all the classes needed to beautifully develop your robot.
// #include <Sensors.h>
// #include <Led.h>
#include <Motors.h>
// #include <Memory.h>
// #include <Moti.h>

// Then create instances of every classes
// Sensors sensors;
Motors motors;
// Moti moti;

int time;
unsigned long previousMillis = 0;
bool out = false;


void setup() {
	// moti.initDebug(sensors, motors);
	motors.init();
	
}

void loop() {
	motors.goForward();
	delay(2000);
	motors.spinRight();
	delay(1000);
	motors.spinLeft();
	delay(1000);

}
