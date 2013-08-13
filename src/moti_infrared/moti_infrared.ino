//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file moti_infrared.ino
 * @brief moti_infrared.ino is used for define the robot behaviours need to draw one figure.
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

int infraRougePinAvance = A0, infraRougePinGauche = A1, infraRougePinDroite = A2;
int readAvance, readGauche, readDroite;

/**
 * @class INFRAREDDETECTION
 * @brief The INFRAREDDETECTION class is used to detect the value of the infrared sensor.
 *
 * This class reads 10 followed values from the sensor and does the median. 
 */

void infraRedDetection (int n) {

int some1 = 0, some2 = 0, some3 = 0;   //Auxiliaire Variables

for (int i = 1; i<=n; i++){

some1 += analogRead(infraRougePinAvance);       
some2 += analogRead(infraRougePinGauche);
some3 += analogRead(infraRougePinDroite);

}

readAvance = some1/n; 	  		 // @ Median mesure for filter the extremes values. 
readGauche = some2/n;			 // @ Median mesure for filter the extremes values. 
readDroite = some3/n; 			 // @ Median mesure for filter the extremes values. 

}

/**
 * @class INFRAREDDETECTION
 * @brief The INFRAREDDETECTION class is used to detect the value of the infrared sensor.
 *
 * This class reads 10 followed values from the sensor and does the median. 
 */

void infraRedBehaviour() {

Motors.stop();
int aux1, aux2, aux3;		// @ Auxiliaires Variables for save the informations of the past and allows to analyse and calculate the dynamics.
infraRedDetection(10);
aux1 = readAvance;
aux2 = readGauche;
aux3 = readDroite;
infraRedDetection(10);


int mod = sqrt((readAvance - aux1)*(readAvance - aux1) + (readGauche - aux2)*(readGauche - aux2) + (readDroite - aux3)*(readDroite - aux3)); 
// @ Calculation of variation module for allow to differentiate sweet movements and sudden movements.


if (readAvance > ((readDroite + readGauche)/2) + 100) {   // @ Comparation between goForward and goBackward in fonction of the three infrared sensors.

	Motors.goForward();
	delay (100);

}


else if (readAvance + 100 < ((readDroite + readGauche)/2)) {   // @ Comparation between goForward and goBackward in fonction of the three infrared sensors.

	Motors.goBackward();
	delay (100);

}

}


void infraRedMap () {}

void infraRedSettings () {}



void setup() {
	Moti.initVerbose();
}



//######//
// LOOP //
//######//

void loop() {

delay(100);

infraRedDetection(10);
Serial.print(readAvance);
Serial.print(" ");
Serial.print(readGauche);
Serial.print(" ");
Serial.print(readDroite);
Serial.print("\n");
infraRedBehaviour();

}

