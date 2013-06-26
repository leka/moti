//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include "Arduino.h"

#include "Moti.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

MOTI Moti = MOTI();


//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
}



//######//
// LOOP //
//######//

void loop() {
	Serial.println("Starting loop");
	Serial.println("Going forward");
	Moti.goForward();
	delay(5000);
	Serial.println("Blinking Led");
	Moti.blinkLed(4);
	delay(2000);
	Serial.println("Spinning right");
	Moti.spinRight();
	delay(2000);
	Serial.println("Stopping");
	Moti.stop();
	delay(2000);
	Serial.println("Blinking Led");
	Moti.blinkLed(10);
	delay(1000);
	Serial.println("Finishing loop");
}
