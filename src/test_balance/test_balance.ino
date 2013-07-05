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

void Balance (){


	Moti.checkGyroscope();
	Serial.println(Moti.getYPR(0));


	while (abs(Moti.getYPR(0)) > 3) { 	


		Moti.checkGyroscope();	


		if(Moti.getYPR(0) < 0){

			Moti.spinRight();
		
		}
	
		else {

			Moti.spinLeft();

		}

	}


	while (abs(Moti.getYPR(1)) > 3) { 	


		Moti.checkGyroscope();	


		if(Moti.getYPR(1) < 0){

			Moti.goForward();
		
		}
	
		else {

			Moti.goBackward();

		}
	}

	//Je dois penser comme corriger l'axis R 


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
	
	Balance();

}

