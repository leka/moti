//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file balance.ino
 * @brief balance.ino is used for stabilize the Robot in one position (Initial Position).
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


MOTI Moti = MOTI();


/**
 * @class BALANCE
 * @brief The BALANCE class represents the stabilization of the robot in the start position.
 *
 * This class corrects the variation of the initial position of the robot inside the ball to be everytime in the same position relative.
 */

void Balance (){


	Moti.checkGyroscope();  //@ Check the Gyroscope initial values.


	while (abs(Moti.getYPR(0)) > 3) { 	//@ How these values are initializes at zero, they are compared with -3 and 3 and do the position upgrade with this tolerance.
										

		Moti.checkGyroscope();	

		if(Moti.getYPR(0) < 0){		Moti.spinRight();	}   //@ If the value is negatif, the derivate is positive and go back to zero.
	
		else {		Moti.spinLeft();		}	 //@ If the value is positive, the derivate is negative and go back to zero.


	} 


	while (abs(Moti.getYPR(2)) > 10) { 	//@ How these values are initializes at zero, they are compared with -10 and 10 and do the position upgrade with this tolerance.
										

		Moti.checkGyroscope();	

		if(Moti.getYPR(2) > 0){ Moti.spinRight(); } //@ If the value is negatif, the derivate is positive and go back to zero and the inclination...
													//@ at YPR(2) is changed for one inclination at YPR(1) due to the ball geometry.
		else { Moti.spinLeft(); }


	} 


	while (abs(Moti.getYPR(1)) > 3) { 	//@ YPR(1) finally correct the error in YPR(2) after the rotation and work independent.
 

		Moti.checkGyroscope();	

		if(Moti.getYPR(1) < 0){ Moti.goForward(); } //@ If the value is negatif, goForward allows to go back to zero.
												
		else { Moti.goBackward(); }	//@ If the value is positive, goBackward allows to go back to zero.


	} 


	Moti.stop(); //

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
//Moti.spinRight();

}

