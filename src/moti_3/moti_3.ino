//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include "Arduino.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

#include "Moti.h"

MOTI Moti = MOTI();
RGBLED rgbled = RGBLED(9, 10,11);
FreeSixIMU AccelGyro = FreeSixIMU();

int led = 13;

//#######//
// SETUP //
//#######//

void setup() {
	Serial.begin(115200);
	pinMode(led, OUTPUT);
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
