//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//


#include <Arduino.h>
#include <Wire.h>
#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

// Include all the classes needed to beautifully develop your robot.
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Memory.h>
#include <Moti.h>

// Then create instances of every classes
Sensors sensors;
Led led;
Motors motors;
Moti moti;

void setup() {
	moti.initDebug(sensors, motors, led);
}

void loop() {
<<<<<<< HEAD
	sensors.checkSensors();
	moti.sendJson(sensors);
	delay(moti.getLoopDelay());
}
=======
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
>>>>>>> dc39ef3074f029801cb09cf35d330a5854c05418
