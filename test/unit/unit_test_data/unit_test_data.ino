
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

int time1, time2, delta;
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
	Serial.println();
	Serial.println(F("Starting Loop"));
	delay(1000);

	Serial.println();
	Serial.println(F("Checking Sensors"));
	Moti.checkSensors();
	Serial.println(F("Sending Data for machine learning"));
	Moti.sendDataLearning();
	Serial.println(F("Pause for 1 second"));
	delay(1000);

	Serial.println();
	Serial.println(F("Checking Sensors"));
	Moti.checkSensors();
	Serial.println(F("Sending Data formatted as JSON"));
	Moti.sendDataJson();
	Serial.println(F("Pause for 1 second"));
	delay(1000);

	Serial.println();
	Serial.println(F("Calculating time necessary to check sensors"));
	time1 = millis();
	Moti.checkSensors();
	time2 = millis();
	Serial.print(F("Time 1 = "));
	Serial.println(time1);
	Serial.print(F("Time 2 = "));
	Serial.println(time2);
	delta = time2 - time1;
	Serial.print(F("Time spent = "));
	Serial.println(delta);
	delay(1000);

	Serial.println();
	Serial.println(F("Ending Loop"));
	delay(1000);

	delay(4000);
}