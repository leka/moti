
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
 loop() {
	Serial.println();
	Serial.println(F("Starting Loop"));
	delay(1000);

	Serial.println();
	Serial.println(F("Setting  Sensors"));



	Serial.println(F("Pause for 1 second"));
	delay(1000);


	Serial.println();
	Serial.println(F("Ending Loop"));
	delay(1000);

	delay(4000);
}