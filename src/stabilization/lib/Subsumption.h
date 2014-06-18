#ifndef LEKA_MOTI_BEHAVIORS_H
#define LEKA_MOTI_BEHAVIORS_H

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "DriveSystem.h"
#include "Sensors.h"
#include "Led.h"

// OBJECTS
Sensors sensors;
Led heart = Led(11, 12, 13);
DriveSystem robot;

// WORKING AREAS
static WORKING_AREA(waArbitrerThread, 800);
static WORKING_AREA(waStabilizationThread, 400);
static WORKING_AREA(waCruiseThread, 400);
static WORKING_AREA(waBumpThread, 900);


// EVENTS
eventmask_t cruiseEvent = 1; // 0b001;
eventmask_t bumpEvent = 2; // 0b010;
eventmask_t stabilizationEvent = 4; // 0b100;

// STATES
bool_t sleeping = TRUE;

// THREADS
Thread * ArbitrerThd;
Thread * CruiseThd;
Thread * StabilizationThd;
Thread * BumpThd;

#endif // LEKA_MOTI_BEHAVIORS_H
