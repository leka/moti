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
	/**
	 * First, we check if any serial commands were sent to the robot. If so, we enter the remote control state and stop the standard execution of void loop().
	 */
	Moti.serialServer();

	/**
	 * Then, if there is no serial command to execute, the robot goes on and lives a happy life.
	 */
	Moti.goForward();
	delay(7000);
	Moti.spinRight();
	delay(600);
	Moti.goForward();
	delay(5000);
	Moti.spinLeft();
	delay(1200);
	Moti.goRight();
	delay(7000);
	Moti.stop();
	delay(2000);

	Moti.checkSensors();
	Moti.sendDataJson();

	delay(Moti.getLoopDelay());
}




