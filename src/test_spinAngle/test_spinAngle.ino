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


int theta, delta, mcycle, angle;


MOTI Moti = MOTI();


void MotorSpinRightAngle(int spin) { //Angle entre 0 et 180
	
	Moti.checkGyroscope();
	
	mcycle = int(spin/360);
	spin = spin%360;

	
	for (int i = 0; i < mcycle; i++) {

		theta = Moti.getYPR(0);
		delta = 0;
		
		while (abs(delta - 360) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < 360){ Moti.spinRight(); }
	
		else { Moti.spinLeft(); }

		angle = Moti.getYPR(0);

		if (angle < theta){angle = angle + 360;}
		
		delta = abs(angle - theta);
	
		}

	
	}


	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;
	

	while (abs(delta - spin) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < spin){ Moti.spinRight(); }
	
		else { Moti.spinLeft(); }

		angle = Moti.getYPR(0);

		if (angle < theta){angle = angle + 360;}
		delta = abs(angle - theta);

	}

	Moti.stop();

	}


void MotorSpinLeftAngle(int spin) {  //Angle entre 0 et 180

	Moti.checkGyroscope();
	
	mcycle = int(spin/360);
	spin = spin%360;

	
	for (int i = 0; i < mcycle; i++) {

		theta = Moti.getYPR(0);
		delta = 0;
		
		while (abs(delta - 360) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < 360){ Moti.spinLeft(); }
	
		else { Moti.spinRight(); }

		angle = Moti.getYPR(0);

		if (angle > theta){angle = angle - 360;}
		
		delta = abs(angle - theta);
	
		}

	
	}


	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;

	
	while (abs(delta - spin) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < spin){ Moti.spinLeft(); }
	
		else { Moti.spinRight(); }

		angle = Moti.getYPR(0);

		if (angle > theta){angle = angle - 360;}
		
		delta = abs(angle - theta);

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


MotorSpinLeftAngle(900);
delay(1500);
MotorSpinRightAngle(1260);
delay(1500);


}

