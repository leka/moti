#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t ArbitrerThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&ArbitrerSem);
		// serial.println("Arbitrer");
		// serial.println(getBehavior());

		if (sensors.getXYZ(2) > 450) {
			setBehavior(EXPLORE);
		}

		else if (getBehavior() == WAITING) {
			_elapsedWaintingTime = chTimeNow() - _startWaitingTime;
			// serial.println(_elapsedWaintingTime);
			// serial.println(_numberOfCallsForInteraction);
		}

		else if (getBehavior() == WAITING || _elapsedWaintingTime > 10000) {
			setBehavior(WANT_INTERACTION);
			_elapsedWaintingTime = 0;
		}

		else if (_numberOfCallsForInteraction > 2) {
			setBehavior(SLEEP);
			_numberOfCallsForInteraction = 0;
		}

		chSemSignal(&DriveSem);
		chSemSignal(&LightSem);
	}
}