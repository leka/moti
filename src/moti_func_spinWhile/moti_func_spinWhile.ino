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

int angle1, angle2, delta = 0;

int spin = 90;
int i = 0;
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
	Moti.checkSensors();


	angle1 = Moti.getYPR(0);
	angle2 = angle1;

	delta = angle1 - angle2;


	while(abs(delta) < spin){
		Moti.spinLeft();
		Moti.checkSensors();

		angle2 = Moti.getYPR(0);

		delta = angle2 - angle1;

		Serial.print(angle1);
		Serial.print(" | ");
		Serial.print(angle2);
		Serial.print(" | ");
		Serial.print(delta);
		Serial.print(" | ");
		Serial.println("Pas bon");

		delay(500);

	}

	Serial.println("OK!");

	delay(500);

}
