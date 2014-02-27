#define serial Serial

#include <Arduino.h>
#include "ChibiOS_AVR.h"

#include "Behaviors.h"

static msg_t SensorThreadFunction(void *arg) {
	(void)arg;

	systime_t nextTime = chTimeNow();

	while (TRUE) {
		nextTime += MS2ST(500);
		sensors.read();
		chSemSignal(&ArbitrerSem);
		chThdSleepUntil(nextTime);

		serial.print(F("Unused Stack Arbitrer: "));
		serial.println(chUnusedStack(waArbitrerThread, sizeof(waArbitrerThread)));

		serial.print(F("Unused Stack Heart: "));
		serial.println(chUnusedStack(waHeartThread, sizeof(waHeartThread)));

		serial.print(F("Unused Stack Light: "));
		serial.println(chUnusedStack(waLightThread, sizeof(waLightThread)));

		serial.print(F("Unused Stack Drive: "));
		serial.println(chUnusedStack(waDriveThread, sizeof(waDriveThread)));

		serial.print(F("Unused Stack Sensor: "));
		serial.println(chUnusedStack(waSensorThread, sizeof(waSensorThread)));
	}
	return 0;
}