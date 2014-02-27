#define serial Serial

#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"

#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"

#include "Sensors.h"
#include "Led.h"
#include "Motor.h"
#include "DriveSystem.h"

#include "../../lib/Subsumption/Arbitrer.h"
#include "../../lib/Subsumption/Cruise.h"
#include "../../lib/Subsumption/Bump.h"
#include "../../lib/Subsumption/Stabilization.h"

Led led = Led(11, 12, 13);

void chSetup() {
	/*chThdCreateStatic(waArbitrerThread, sizeof(waArbitrerThread),
		NORMALPRIO + 10, ArbitrerThread, NULL);
	// chThdCreateStatic(waStabilizationThread, sizeof(waStabilizationThread),
	// 	NORMALPRIO, StabilizationThread, NULL);
	chThdCreateStatic(waCruiseThread, sizeof(waCruiseThread),
		NORMALPRIO + 1, CruiseThread, NULL);
	chThdCreateStatic(waBumpThread, sizeof(waBumpThread),
		NORMALPRIO + 2, BumpThread, NULL);*/
	
	uint16_t n = 0;
	uint32_t t = 0;
	Serial.println("Yolo");

	/*t = chTimeNow();
	while (chTimeNow() - t < 7500) {
		Serial.println(chTimeNow() - t);
	}
	t = 0; */

	robot.go(FORTH, 220, 1500);

	Serial.println("YOLO");

	t = chTimeNow();
	while (chTimeNow() - t < 500);
	t = 0;

	/*while (1) {
		sensors.readAccelerometer();
		
		if (sensors.getXYZ(0) > 120) {
			if (t == 0)
				t = chTimeNow();
		}
		else {
			t = 0;
			robot.go(FORTH, 220);
			led.turnOff();
		}

		if ((t != 0) && (chTimeNow() - t > 700)) {
			robot.stop();
			led.shine(RED);
			Serial.println("Swag :(");
		}
	}*/

	robot.stop(3000);

	Serial.println("Swag");

	//robot.stop();
}

void setup() {
	Serial.begin(115200);
	sensors.init();

	chBegin(chSetup);

	while(1) {
		// nothing to do here
	}
}

void loop() {
	// nothing to do here
}
