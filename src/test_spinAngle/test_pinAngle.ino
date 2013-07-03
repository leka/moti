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

void MotorSpinRightAngle(int Aspeed, int angle) {

	Moti.spinRight(Aspeed);
	delay(angle*25);
	Moti.stop();

}

void MotorSpinLeftAngle(int Aspeed, int angle) {

	Moti.spinLeft(Aspeed);
	delay(angle*25);
	Moti.stop();
}


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
	
delay(5000);	
MotorSpinRightAngle(255,90);
delay(2000);
MotorSpinLeftAngle(255,90);
delay(2000);
MotorSpinRightAngle(255,180);
delay(2000);
MotorSpinLeftAngle(255,180);
delay(2000);
MotorSpinRightAngle(255,360);
delay(2000);
MotorSpinLeftAngle(255,360);
delay(2000);


}

