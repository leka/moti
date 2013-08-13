//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file moti_ultrasound.ino
 * @brief moti_ultrasound.ino is used for define the robot behaviours need to draw one figure.
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


//#######//
// SETUP //
//#######//

float Map [];
int theta0;

void ultrasonDetection () {   //@ Depends of the sensor that has been choosed. 

pulseIn ();

DigitalRead ();	

}


void ultrasonMap (int n) {  //@ Mapping of the distances in 360 degrees

	theta0 = Moti.getGyro(P); //@ Get starting angle 
	
	for (i = 0; i< n ; i ++){
	SpinLeftAngle(360/n);			//@ Rotate Step 
	Map[i] = ultrasonDetection();}	//@ Get the distance during one rotation

}


void ultrasonSettings () {}


void setup() {
	Moti.initVerbose();
}



//######//
// LOOP //
//######//

void loop() {

ultrasonMap();


}

