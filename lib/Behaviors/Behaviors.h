#ifndef LEKA_MOTI_ARDUINO_BEHAVIORS_H_
#define LEKA_MOTI_ARDUINO_BEHAVIORS_H_

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
Led light = Led(8, 9, 10);

//	BEHAVIORS
enum Behaviors {
	WAKE_UP,
	EXPLORE,
	WAITING,
	WANT_INTERACTION,
	SLEEP
};

//	SEMAPHORES
SEMAPHORE_DECL(ArbitrerSem, 0);
SEMAPHORE_DECL(DriveSem, 0);
SEMAPHORE_DECL(LightSem, 0);
// SEMAPHORE_DECL(CallSem, 0);
// SEMAPHORE_DECL(SleepSem, 0);

//	MUTEXES
MUTEX_DECL(BehaviorMutex);
MUTEX_DECL(WaitingTimeMutex);

//	THREADS
// Thread * SensorThread;
// Thread * ArbitrerThread;
// Thread * HeartThread;
// Thread * LightThread;
// Thread * DriveThread;

//	VARIABLES
volatile uint8_t _bpm = 15;
volatile systime_t _waitingTime = 0;
volatile systime_t _startWaitingTime = 0;
volatile systime_t _elapsedWaintingTime = 0;
volatile uint8_t _behavior = SLEEP;
volatile uint8_t _numberOfCallsForInteraction = 0;

//	STATES
volatile bool isStarting = TRUE;
volatile bool isWakingUp = FALSE;
volatile bool isWaiting = FALSE;
volatile bool noInteractionForTooLong = FALSE;

//	WORKING AREA
static WORKING_AREA(waArbitrerThread, 50);
static WORKING_AREA(waHeartThread, 50);
static WORKING_AREA(waLightThread, 40);
static WORKING_AREA(waDriveThread, 250);
static WORKING_AREA(waSensorThread, 256);

//	METHODS
void setBehavior(Behaviors behavior) {
	chMtxLock(&BehaviorMutex);
		_behavior = behavior;
	chMtxUnlock();
}

uint8_t getBehavior() {
	return _behavior;
}

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
#endif