#ifndef LEKA_MOTI_ARDUINO_THREAD_H_
#define LEKA_MOTI_ARDUINO_THREAD_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Sensors.h"
#include "Led.h"
#include "DriveSystem.h"

//	SENSORS
Sensors sensors;

//	MOTORS
DriveSystem driveSystem;

//	LED
Led heart = Led(11, 12, 13);
Led sleep = Led(8, 9, 10);

//	GLOBAL VARIABLES
volatile uint8_t bpm = 15;

//	SEMAPHORES
SEMAPHORE_DECL(AnalyzerSem, 0);
SEMAPHORE_DECL(WakeUpSem, 0);
SEMAPHORE_DECL(ExploreSem, 0);
SEMAPHORE_DECL(CallSem, 0);
SEMAPHORE_DECL(SleepSem, 0);

//	THREADS
Thread * SensorThread;
Thread * AnalyzerThread;
Thread * SleepThread;
Thread * HeartThread;
Thread * WakeUpThread;
Thread * ExploreThread;
Thread * CallThread;

//	VARIABLES
volatile systime_t elapsedTime = 0;
volatile systime_t startTime = 0;

//	STATES
volatile bool isStarting = TRUE;
volatile bool isWakingUp = FALSE;
volatile bool isWaiting = FALSE;
volatile bool noInteractionForTooLong = FALSE;

//	WORKING AREA
static WORKING_AREA(waHeartThread, 260);
static WORKING_AREA(waSleepThread, 260);
static WORKING_AREA(waWakeUpThread, 260);
static WORKING_AREA(waSensorThread, 260);
static WORKING_AREA(waAnalyzerThread, 260);
static WORKING_AREA(waExploreThread, 260);
static WORKING_AREA(waCallThread, 260);

#endif