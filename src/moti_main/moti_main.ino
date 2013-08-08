//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//


#include <Arduino.h>

// Include all the classes needed to beautifully develop your robot.
#include <Moti.h>
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Speakers.h>
#include <Memory.h>

// Then create instances of every classes
Moti moti;
Sensors sensors;
Led led;
Motors motors;
Speakers speakers;

void setup() {
	// Initialize moti
	moti.init();
}

void loop() {
	motors.goForward();
	delay(5000);
	led.blinkLed(RAND, 5, 200);
	delay(2000);
	motors.spinRight();
	delay(2000);
	motors.stop();
	delay(2000);
	led.blinkLed(RAND, 5, 100);
	delay(1000);
}