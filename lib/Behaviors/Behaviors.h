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
// SEMAPHORE_DECL(WakeUpSem, 0);
// SEMAPHORE_DECL(ExploreSem, 0);
// SEMAPHORE_DECL(CallSem, 0);
// SEMAPHORE_DECL(SleepSem, 0);

//	THREADS
Thread * SensorThread;
Thread * ArbitrerThread;
Thread * HeartThread;
Thread * LightThread;
Thread * DriveThread;

//	VARIABLES
volatile uint8_t _bpm = 15;
volatile systime_t _elapsedTime = 0;
volatile systime_t _startTime = 0;
volatile uint8_t _behavior = SLEEP;

//	STATES
volatile bool isStarting = TRUE;
volatile bool isWakingUp = FALSE;
volatile bool isWaiting = FALSE;
volatile bool noInteractionForTooLong = FALSE;

//	WORKING AREA
static WORKING_AREA(waArbitrerThread, 260);
static WORKING_AREA(waHeartThread, 260);
static WORKING_AREA(waLightThread, 260);
static WORKING_AREA(waDriveThread, 260);
static WORKING_AREA(waSensorThread, 260);

//	METHODS
void setBehavior(Behaviors behavior) {
	_behavior = behavior;
}

uint8_t getBehavior() {
	return _behavior;
}
#endif