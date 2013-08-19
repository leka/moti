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
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Memory.h>
#include <Moti.h>

// Then create instances of every classes
Sensors sensors;
Led rightLed = Led(8, 9, 10);
Led leftLed = Led(11, 12, 13);
Motors motors;
Moti moti;

int currT;
int milli = 0;
void setup() {
	serial.begin(115200);
	rightLed.init();
	leftLed.init();
	
}

void loop() {
	currT = millis() - milli;

	if (currT < 10000){
		serial.print("AAAA  ");
		serial.println(currT);

		leftLed.blinkSync(RED, 5, 500);
		rightLed.blinkSync(BLUE, 10, 300);
	}
	if(currT > 10000 && currT < 15000 ){
		serial.print("BBBB  ");
		serial.println(currT);
	}
	if(currT > 15000){
		serial.print("CCCC  ");
		serial.println(currT);
		leftLed.blinkSync(GREEN, 3, 1000);
		rightLed.blinkSync(YELLOW, 5, 250);
	}
	if(currT > 20000){
		currT = 0;
		milli = millis();
		serial.println(currT);
		delay(1000);
	}



	delay(moti.getLoopDelay());
}