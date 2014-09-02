#ifndef LEKA_MOTI_BEHAVIOR_STABILIZATION_H_
#define LEKA_MOTI_BEHAVIOR_STABILIZATION_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"
#include "Moti.h"
#include "Motion.h"

namespace Stabilization {

	// Functions prototypes
	static msg_t stabilizationThread(void* arg);
	void start(void* arg=NULL, tprio_t priority=NORMALPRIO);
	void run(void);
	void stop(void);

	// Variables
	static WORKING_AREA(stabilizationThreadArea, 256);
	static bool _isStarted = false;
	static bool _isRunning = false;

}

#endif

