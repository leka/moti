#ifndef LEKA_MOTI_ARDUINO_THREAD_SETUP_H_
#define LEKA_MOTI_ARDUINO_THREAD_SETUP_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "SensorThread.h"
#include "ArbitrerThread.h"
#include "HeartThread.h"
#include "DriveThread.h"
#include "LightThread.h"

void chSetup() {

	SensorThread = chThdCreateStatic(waSensorThread, sizeof(waSensorThread),
				NORMALPRIO + 11, SensorThreadFunction, NULL);
	ArbitrerThread = chThdCreateStatic(waArbitrerThread, sizeof(waArbitrerThread),
				NORMALPRIO + 11, ArbitrerThreadFunction, NULL);
	DriveThread = chThdCreateStatic(waDriveThread, sizeof(waDriveThread),
				NORMALPRIO, DriveThreadFunction, NULL);
	HeartThread = chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
				NORMALPRIO + 12, HeartThreadFunction, NULL);
	LightThread = chThdCreateStatic(waLightThread, sizeof(waLightThread),
				NORMALPRIO, LightThreadFunction, NULL);
}

#endif