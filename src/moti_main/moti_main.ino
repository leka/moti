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
	Moti.goForward();
	Moti.printRgbColor(35, 167, 210);
	delay(5000);
	Moti.printRgbColor(65, 30, 110);
	delay(1000);
	Moti.printRgbColor(35, 167, 210);
	delay(1000);
	Moti.printRgbColor(65, 30, 110);
	//Moti.spinRight();
	delay(1000);
	Moti.printRgbColor(35, 167, 210);
	delay(1000);
	Moti.printRgbColor(65, 30, 110);
	delay(1000);
	Moti.printRgbColor(35, 167, 210);
	delay(1000);
	Moti.printRgbColor(65, 30, 110);
	delay(1000);

}
