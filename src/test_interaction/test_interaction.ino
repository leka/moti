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


int thetaY, thetaP, thetaR, accX, accY, accZ;
String status, gyroY, gyroP, gyroR, accelX, accelY, accelZ;


MOTI Moti = MOTI();



void interaction() {

Moti.checkSensors();
thetaY = Moti.getYPR(0); thetaP = Moti.getYPR(1); thetaR = Moti.getYPR(2);
accX = Moti.getXYZ(0); accY = Moti.getXYZ(1); accZ = Moti.getXYZ(2);

delay (1000);

Moti.checkSensors();

if ((Moti.getYPR(0) - thetaY) > 8){ gyroY = "Oui"; }

else { gyroY = "Non"; }



if ((Moti.getYPR(1) - thetaP) > 8){ gyroP = "Oui"; }

else { gyroP = "Non"; }



if ((Moti.getYPR(2) - thetaR) > 8){ gyroR = "Oui"; }

else { gyroR = "Non"; }



if ((Moti.getXYZ(0) - accX) > 8){ accelX = "Oui"; }

else { accelX = "Non"; }



if ((Moti.getXYZ(1) - accY) > 8){ accelY = "Oui"; }

else { accelY = "Non"; }



if ((Moti.getXYZ(2) - accZ) > 8){ accelZ = "Oui"; }

else { accelZ = "Non"; }


status = "GyroY: " + gyroY + " || " + " GyroP: " + gyroP + " || " + " GyroR: " + gyroR + " || " + " AccelX: " + accelX + " || " + " AccelY: " + accelY + " || " + "AccelZ: " + accelZ; 


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

interaction();
Serial.println(status);

}

