//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file moti_interaction.ino
 * @brief moti_interaction.ino is used for define the robot behaviours need to draw one figure.
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


int thetaY, thetaP, thetaR, accX, accY, accZ;
String status, gyroY, gyroP, gyroR, accelX, accelY, accelZ;


MOTI Moti = MOTI();

/**
 * @class INTERACTION
 * @brief The INTERACTION class is used to test the sensors accelerometer and gyroscope.
 *
 * This class reads the sensor values and show in the screen by the serial port. 
 */

void interaction() {

Sensors.checkSensors();
thetaY = Sensors.getYPR(0); thetaP = Sensors.getYPR(1); thetaR = Sensors.getYPR(2);
accX = Sensors.getXYZ(0); accY = Sensors.getXYZ(1); accZ = Sensors.getXYZ(2);

delay (1000);

Sensors.checkSensors();

if ((Sensors.getYPR(0) - thetaY) > 8){ gyroY = "Oui"; }

else { gyroY = "Non"; }



if ((Sensors.getYPR(1) - thetaP) > 8){ gyroP = "Oui"; }

else { gyroP = "Non"; }



if ((Sensors.getYPR(2) - thetaR) > 8){ gyroR = "Oui"; }

else { gyroR = "Non"; }



if ((Sensors.getXYZ(0) - accX) > 8){ accelX = "Oui"; }

else { accelX = "Non"; }



if ((Sensors.getXYZ(1) - accY) > 8){ accelY = "Oui"; }

else { accelY = "Non"; }



if ((Sensors.getXYZ(2) - accZ) > 8){ accelZ = "Oui"; }

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

