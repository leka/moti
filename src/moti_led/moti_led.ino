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
Led rightLed;
Led leftLed = Led(11, 12, 13);
Motors motors;
Moti moti;


void setup() {
	Serial1.begin(115200);
	Serial.println("SC");
	moti.initDebug(sensors, motors, rightLed);
	leftLed.init();
	
}

void loop() {
	if (millis() < 10000){
		Serial1.println("1");
		leftLed.blinkSync(RED, 5, 500);
		rightLed.blinkSync(BLUE, 10, 100);
	}
	if(millis() > 10000 && millis() < 15000 ){
		Serial1.println("2");
		leftLed.turnOff();
		rightLed.turnOff();
	}
	if(millis() > 15000){
		Serial1.println("3");
		leftLed.blinkSync(GREEN, 3, 1000);
		rightLed.blinkSync(YELLOW, 5, 100);
	}



	delay(moti.getLoopDelay());
}