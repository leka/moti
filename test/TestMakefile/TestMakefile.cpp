#include <Arduino.h>

#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "DriveSystem.h"
#include "Motor.h"
#include "Led.h"

DriveSystem motors;
Led light = Led(8, 9, 10);

void setup() {

	Serial.begin(115200);
	delay(2000);

	Serial.println("Robot starting");

}

void loop() {

	motors.go();
	delay(5000);
	motors.stop();

	delay(5000);

	light.shine(BLUE);
	delay(500);
	light.shine(RED);
	delay(500);
	light.shine(GREEN);
	delay(500);
	light.turnOff();

	delay(5000);
}
