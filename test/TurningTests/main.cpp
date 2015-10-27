

#include <Arduino.h>
#include <Wire.h>

#include "Sensors.h"
#include "Motion.h"
#include "Moti.h"
#include "Light.h"


#include "Heart.h"
#include "Stabilization.h"



//Led heart = Led(11, 12, 13);

void mainThread() {

	Sensors::init();
	Moti::init();
	Heart::init();

	Stabilization::init();

	Sensors::start();
	Moti::start();
	Heart::start();



	while (TRUE) {
	// DriveSystem::turn(FORWARD,130,0);
	// waitMs(1000);
	// DriveSystem::turn(FORWARD,0,130);
	Stabilization::wiggle();
	waitMs(100);

	}
}

void loop() { }

int main(void) {
	init();

	Serial.begin(115200);

	while(!Serial);

	Wire.begin();
	delay(500);

	chBegin(mainThread);

	while(1);

	return 0;
}
