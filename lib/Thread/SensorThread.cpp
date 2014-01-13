// #define serial Serial

// #include <Arduino.h>
// #include "ChibiOS_AVR.h"

// #include "Thread.h"

// static msg_t SensorThread(void *arg) {
// 	(void)arg;

// 	systime_t time = chTimeNow();

// 	while (TRUE) {
// 		time += MS2ST(100);
// 		sensors.read();
// 		chSemSignal(&SensorSem);
// 		chThdSleepUntil(time);
// 	}
// 	return 0;
// }