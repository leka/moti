//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//


#include <Arduino.h>
#include <Wire.h>
#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

// Include all the classes needed to beautifully develop your robot.
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Memory.h>

// Then create instances of every classes
Sensors sensors;
Led led;
Motors motors;

void setup() {
	// Initialize moti
	Serial.begin(115200);
	Serial.println("SC");
	led.init();
	Serial.println("LED");
	motors.init();
	Serial.println("MT");
	sensors.init();
	Serial.println("IMU");
}

void loop() {
	motors.goForward();
	delay(2000);
	motors.stop();
	sensors.checkSensors();
	sensors.sendJson();
	delay(200);
}