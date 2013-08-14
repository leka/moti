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
#include <Moti.h>

// Then create instances of every classes
Sensors sensors;
Led led;
Motors motors;
Moti moti;

void setup() {
	moti.initDebug(sensors, motors, led);
	moti.setLoopDelay(200);
}

void loop() {
	sensors.checkSensors();
	moti.sendJson(sensors);
	delay(moti.getLoopDelay());
}