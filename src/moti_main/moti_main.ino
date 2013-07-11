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
	Moti.printRgbColor(RED);
	delay(10000);
	Moti.printRgbColor(BLUE);
	Moti.blinkLed(RAND, 4, 50);
	Moti.printRgbColor(GREEN);
	delay(2000);
	Moti.printRgbColor(DARK_ORANGE);
	Moti.spinRight();
	Moti.printRgbColor(YELLOW);
	delay(4000);
	Moti.printRgbColor(WHITE);
	Moti.stop();
	Moti.printRgbColor(RAND);
	delay(2000);
	Moti.printRgbColor(RAND);
	Moti.blinkLed(RAND, 10, 50);
	delay(1000);

}
