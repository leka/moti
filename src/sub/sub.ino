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

void chSetup() {
	chThdCreateStatic(waArbitrerThread, sizeof(waArbitrerThread),
		NORMALPRIO + 10, ArbitrerThread, NULL);
	// chThdCreateStatic(waStabilizationThread, sizeof(waStabilizationThread),
	// 	NORMALPRIO, StabilizationThread, NULL);
	chThdCreateStatic(waCruiseThread, sizeof(waCruiseThread),
		NORMALPRIO + 1, CruiseThread, NULL);
	chThdCreateStatic(waBumpThread, sizeof(waBumpThread),
		NORMALPRIO + 2, BumpThread, NULL);
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
