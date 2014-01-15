#ifndef LEKA_MOTI_ARDUINO_THREAD_SETUP_H_
#define LEKA_MOTI_ARDUINO_THREAD_SETUP_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

// 	#include "Thread.h"
#include "SleepThread.h"

void chSetup() {
	chThdCreateStatic(waSleepThread, sizeof(waSleepThread),
		NORMALPRIO, SleepThread, NULL);

	// chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
	// 	NORMALPRIO, HeartThread, NULL);

	// chThdCreateStatic(waSensorThread, sizeof(waSensorThread),
	// 	NORMALPRIO, SensorThread, NULL);

	// chThdCreateStatic(waAnalyzerThread, sizeof(waAnalyzerThread),
	// 	NORMALPRIO, AnalyzerThread, NULL);
}

#endif