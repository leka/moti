#ifndef LEKA_MOTI_ARDUINO_THREAD_SETUP_H_
#define LEKA_MOTI_ARDUINO_THREAD_SETUP_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "SleepThread.h"
#include "HeartThread.h"
#include "WakeUpThread.h"
#include "SensorThread.h"
#include "AnalyzerThread.h"
#include "ExploreThread.h"
#include "CallThread.h"

// void terminateAllThreads() {
// 	chThdWait(SleepThread);
// 	chThdWait(ExploreThread);
// 	chThdWait(WakeUpThread);
// 	chThdWait(CallThread);
// }

void chSetup() {

	SensorThread = chThdCreateStatic(waSensorThread, sizeof(waSensorThread),
				NORMALPRIO + 11, SensorThreadFunction, NULL);
	AnalyzerThread = chThdCreateStatic(waAnalyzerThread, sizeof(waAnalyzerThread),
				NORMALPRIO + 11, AnalyzerThreadFunction, NULL);
	SleepThread = chThdCreateStatic(waSleepThread, sizeof(waSleepThread),
				NORMALPRIO, SleepThreadFunction, NULL);
	HeartThread = chThdCreateStatic(waHeartThread, sizeof(waHeartThread),
				NORMALPRIO + 12, HeartThreadFunction, NULL);
	WakeUpThread = chThdCreateStatic(waWakeUpThread, sizeof(waWakeUpThread),
				NORMALPRIO, WakeUpThreadFunction, NULL);
	ExploreThread = chThdCreateStatic(waExploreThread, sizeof(waExploreThread),
				NORMALPRIO, ExploreThreadFunction, NULL);
	CallThread = chThdCreateStatic(waCallThread, sizeof(waCallThread),
				NORMALPRIO, CallThreadFunction, NULL);
	// terminateAllThreads();
}

#endif