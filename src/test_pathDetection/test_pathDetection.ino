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


int theta, delta;


MOTI Moti = MOTI();


void MotorSpinRightAngle(int Aspeed, int spin) {

	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;
	Moti.spinRight(Aspeed);
	
	while (abs(delta) < spin) {
	
	Moti.checkGyroscope();	
	delta = Moti.getYPR(0) - theta;
	
	}

	Moti.stop();

}


void MotorSpinLeftAngle(int Aspeed, int spin) {

	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;
	Moti.spinRight(Aspeed);
	
	while (abs(delta) < spin) {

	Moti.checkGyroscope();	
	delta = Moti.getYPR(0) - theta;
	
	}

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

