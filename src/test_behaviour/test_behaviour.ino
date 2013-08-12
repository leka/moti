//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file behaviour.ino
 * @brief behaviour.ino is used for describe the interaction of the robot in diferents emotion states.
 * @author Luan Ferrari
 * @version 1.0
 */

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


String status;


MOTI Moti = MOTI();

Moti.ColorName BLUE;


/**
 * @class BEHAVIOUR
 * @brief The BEHAVIOUR class represents the 
 *
 * This class defines the interaction between the robot and the users to show the emotions. 
 */


void behaviour() {


switch (status) {      //@ Choose the interactions between the toy, sensors and actuators for simulate the human fillings.

	
	case "happy": 

	Moti.blinkLed(BLUE, 3, 500);
	Moti.blinkLed(GREEN, 3, 500);
	Moti.blinkLed(YELLOW, 3, 500);
	Moti.blinkLed(BLUE, 3, 500);
	Moti.blinkLed(GREEN, 3, 500);
	Moti.blinkLed(YELLOW, 3, 500);




	case "sad": 






	case "stressed":







	case "lazy":







	case "tired":







	case "excited":

}


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

status = "happy";
behaviour();

}

