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

int led = 13;

//#######//
// SETUP //
//#######//

void setup() {
	digitalWrite(led, HIGH);
	delay(1000);
	Serial.println("Setup starting");
	digitalWrite(led, LOW);
	Serial.println("Moti instance initialized");
	Moti.init();
	Serial.println("Everythink ready");
	Moti.blinkLed(4);
}



//######//
// LOOP //
//######//

void loop() {
	Serial.println("Starting loop");
	Moti.goForward();
	delay(5000);
	Moti.blinkLed(4);
	delay(2000);
	Moti.spinRight();
	delay(2000);
	Moti.stop();
	delay(2000);
	Moti.blinkLed(10);
	delay(1000);
}
