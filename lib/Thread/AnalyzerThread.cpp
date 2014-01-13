// #define serial Serial

// #include <Arduino.h>
// #include "ChibiOS_AVR.h"

// #include "Thread.h"

// static msg_t AnalyzerThread(void *arg) {
// 	(void)arg;

// 	while (TRUE) {
// 		chSemWait(&SensorSem);
// 		if (sensors.getXYZ(0) > 300) {
// 			serial.println("ça marche!");
// 		}
// 	}
// }