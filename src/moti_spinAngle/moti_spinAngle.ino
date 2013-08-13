//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file moti_spinAngle.ino
 * @brief moti_spinAngle.ino is used for define the robot behaviours need to draw one figure.
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


int theta, delta, mcycle, angle;


MOTI Moti = MOTI();


/**
 * @class MOTORSPINRIGHTANGLE
 * @brief The MOTORSPINRIGHTANGLE class is used to say for the robot to turn one specific angle in the right direction.
 *
 * This class reads the initial angle and compare with the giroscope for turn the angle specified in the right direction.
 * It uses the algorithm of angle mesure correction to allow turn angles that are higher than one full turn.
 */

void MotorSpinRightAngle(int spin) { // Faire une fonction de spin avec un angle quelconque. 
	
	Sensors.checkGyroscope();
	
	fullTurns = int(spin/360);   // Partie entier avec les quantités des tours complet. 
	spin = spin%360;          // Reste avec l'angle mineur que un tour. 

	
	for (int i = 0; i < fullTurns; i++) {    //Faire des tours complet

		initialAngle = Sensors.getYPR(0);
		deviationAngle = 0;
		
		while (abs(deviationAngle - 360) > 5) { 	

		Sensors.checkGyroscope();	

		if(deviationAngle < 360){ Motors.spinRight(); }
	
		else { Motors.spinLeft(); }

		instantAngle = Sensors.getYPR(0);

		if (instantAngle < initialAngle){instantAngle = instantAngle + 360;}     //Compensation for the signal change of the sensor at -180 and 180.
		
		deviationAngle = abs(instantAngle - initialAngle);
	
		}

	
	}


	Sensors.checkGyroscope();
	initialAngle = Sensors.getYPR(0);
	deviationAngle = 0;
	

	while (abs(deviationAngle - spin) > 5) { 	

		Sensors.checkGyroscope();	

		if(deviationAngle < spin){ Motors.spinRight(); }		// During this time it did not reach the value, it continues turning. 
	
		else { Motors.spinLeft(); }			// If for inercie it passes the exact value, it will return.

		instantAngle = Sensors.getYPR(0);

		if (instantAngle < initialAngle){instantAngle = instantAngle + 360;}        //Compensation for the signal change of the sensor at -180 and 180.
		deviationAngle = abs(instantAngle - initialAngle);

	}

	Motors.stop();

	}


/**
 * @class MOTORSPINLEFTANGLE
 * @brief The MOTORSPINLEFTANGLE class is used to say for the robot to turn one specific angle in the left direction.
 *
 * This class reads the initial angle and compare with the giroscope for turn the angle specified in the left direction.
 * It uses the algorithm of angle mesure correction to allow turn angles that are higher than one full turn.
 */

void MotorSpinLeftAngle(int spin) {  // Any angle


	Moti.checkGyroscope();
	
	fullTurns = int(spin/360);
	spin = spin%360;

	
	for (int i = 0; i < fullTurns; i++) {

		initialAngle = Moti.getYPR(0);
		deviationAngle = 0;
		
		while (abs(deviationAngle - 360) > 5) { 	

		Moti.checkGyroscope();	

		if(deviationAngle < 360){ Moti.spinLeft(); }
	
		else { Moti.spinRight(); }

		instantAngle = Moti.getYPR(0);

		if (instantAngle > initialAngle){instantAngle = instantAngle - 360;}	//Compensation for the signal change of the sensor at -180 and 180.
		
		deviationAngle = abs(instantAngle - initialAngle);
	
		}

	}


	Sensors.checkGyroscope();
	initialAngle = Sensors.getYPR(0);
	deviationAngle = 0;

	
	while (abs(deviationAngle - spin) > 5) { 	

		Sensors.checkGyroscope();	

		if(deviationAngle < spin){ Motors.spinLeft(); }		// During this time it did not reach the value, it continues turning. 
	
		else { Motors.spinRight(); }		// If for inercie it passes the exact value, it will return.

		instantAngle = Sensors.getYPR(0);

		if (instantAngle > initialAngle){instantAngle = instantAngle - 360;}		//Compensation for the signal change of the sensor at -180 and 180.
		
		deviationAngle = abs(instantAngle - initialAngle);

	}

	Motors.stop();

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

