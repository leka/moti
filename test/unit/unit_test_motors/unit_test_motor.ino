
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

	Serial.println(F("Beginning of the Motor Test."));
	delay(2000);

	//// TEST Moti.goForward();////////
	///////////////////////////////////
	Serial.println(F("Moti.goForward(); for 5 seconds."));
	Moti.goForward();
	delay(5000);

	Serial.println(F("Moti.goForward(-100); for 5 seconds."));
	Moti.goForward(-100);
	delay(5000);

	Serial.println(F("Moti.goForward(0); for 5 seconds."));
	Moti.goForward(0);
	delay(5000);

	Serial.println(F("Moti.goForward(100); for 5 seconds."));
	Moti.goForward(100);
	delay(5000);

	Serial.println(F("Moti.goForward(300); for 5 seconds."));
	Moti.goForward(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	//// TEST Moti.goBackward();////////
	///////////////////////////////////
	Serial.println(F("Moti.goBackward(); for 5 seconds."));
	Moti.goBackward();
	delay(5000);

	Serial.println(F("Moti.goBackward(-100); for 5 seconds."));
	Moti.goBackward(-100);
	delay(5000);

	Serial.println(F("Moti.goBackward(0); for 5 seconds."));
	Moti.goBackward(0);
	delay(5000);

	Serial.println(F("Moti.goBackward(100); for 5 seconds."));
	Moti.goBackward(100);
	delay(5000);

	Serial.println(F("Moti.goBackward(300); for 5 seconds."));
	Moti.goBackward(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	//// TEST Moti.goLeft();////////
	///////////////////////////////////
	Serial.println(F("Moti.goLeft(); for 5 seconds."));
	Moti.goLeft();
	delay(5000);

	Serial.println(F("Moti.goLeft(-100); for 5 seconds."));
	Moti.goLeft(-100);
	delay(5000);

	Serial.println(F("Moti.goLeft(0); for 5 seconds."));
	Moti.goLeft(0);
	delay(5000);

	Serial.println(F("Moti.goLeft(100); for 5 seconds."));
	Moti.goLeft(100);
	delay(5000);

	Serial.println(F("Moti.goLeft(300); for 5 seconds."));
	Moti.goLeft(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	//// TEST Moti.goRight();////////
	///////////////////////////////////
	Serial.println(F("Moti.goRight(); for 5 seconds."));
	Moti.goRight();
	delay(5000);

	Serial.println(F("Moti.goRight(-100); for 5 seconds."));
	Moti.goRight(-100);
	delay(5000);

	Serial.println(F("Moti.goRight(0); for 5 seconds."));
	Moti.goRight(0);
	delay(5000);

	Serial.println(F("Moti.goRight(100); for 5 seconds."));
	Moti.goRight(100);
	delay(5000);

	Serial.println(F("Moti.goRight(300); for 5 seconds."));
	Moti.goRight(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	//// TEST Moti.spinLeft();////////
	///////////////////////////////////
	Serial.println(F("Moti.spinLeft(); for 5 seconds."));
	Moti.spinLeft();
	delay(5000);

	Serial.println(F("Moti.spinLeft(-100); for 5 seconds."));
	Moti.spinLeft(-100);
	delay(5000);

	Serial.println(F("Moti.spinLeft(0); for 5 seconds."));
	Moti.spinLeft(0);
	delay(5000);

	Serial.println(F("Moti.spinLeft(100); for 5 seconds."));
	Moti.spinLeft(100);
	delay(5000);

	Serial.println(F("Moti.spinLeft(300); for 5 seconds."));
	Moti.spinLeft(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	//// TEST Moti.spinRight();////////
	///////////////////////////////////
	Serial.println(F("Moti.spinRight(); for 5 seconds."));
	Moti.spinRight();
	delay(5000);

	Serial.println(F("Moti.spinRight(-100); for 5 seconds."));
	Moti.spinRight(-100);
	delay(5000);

	Serial.println(F("Moti.spinRight(0); for 5 seconds."));
	Moti.spinRight(0);
	delay(5000);

	Serial.println(F("Moti.spinRight(100); for 5 seconds."));
	Moti.spinRight(100);
	delay(5000);

	Serial.println(F("Moti.spinRight(300); for 5 seconds."));
	Moti.spinRight(300);
	delay(5000);

	Serial.println(F("Moti.stop(); for 5 seconds."));
	Moti.stop();
	delay(5000);

	Serial.println(F("End of the Motor Test."));
	delay(2000);

}