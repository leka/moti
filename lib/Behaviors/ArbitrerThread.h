#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t ArbitrerThreadFunction(void *arg) {
	(void)arg;

	while (TRUE) {
		chSemWait(&ArbitrerSem);

		serial.println(getBehavior());
		serial.println(_elapsedWaintingTime);

		if (sensors.getXYZ(2) > 450) {
			setBehavior(EXPLORE);
		}

		if (getBehavior() == WAITING) {
			chMtxLock(&WaitingTimeMutex);
				_elapsedWaintingTime = chTimeNow() - _startWaitingTime;
			chMtxUnlock();
		}

		if (_elapsedWaintingTime > 10000) {
			setBehavior(WANT_INTERACTION);

			chMtxLock(&WaitingTimeMutex);
				_elapsedWaintingTime = 0;
			chMtxUnlock();
		}

		if (getBehavior() == WANT_INTERACTION) {
			setBehavior(WAITING);
		}

		if (_numberOfCallsForInteraction > 2) {
			setBehavior(SLEEP);

			chMtxLock(&WaitingTimeMutex);
				_numberOfCallsForInteraction = 0;
			chMtxUnlock();
		}

		chSemSignal(&DriveSem);
		chSemSignal(&LightSem);
	}
}