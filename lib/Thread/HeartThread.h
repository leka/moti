// #include <Arduino.h>
// #include "ChibiOS_AVR.h"

// #include "Thread.h"

// static msg_t HeartThread(void *arg) {

// 	(void)arg;

// 	volatile uint8_t basePwm = 10; // divided by ten to have a wait delay higher than 1ms
// 	volatile uint8_t bpm = 15;     // must multiply by ten in heart.shine();
// 	volatile uint8_t P = 70;
// 	volatile uint8_t Q = 0;
// 	volatile uint8_t R = 150;

// 	while (TRUE) {
// 		heart.fade(40, basePwm, P, 0, 0, 0, 0);
// 		heart.fade(40, P, basePwm, 0, 0, 0, 0);

// 		heart.shine(basePwm, 0, 0);
// 		chThdSleepMilliseconds(80);

// 		heart.fade(60, Q, R, 0, 0, 0, 0);
// 		heart.fade(70, R, basePwm, 0, 0, 0, 0);

// 		chThdSleepMilliseconds(30000/ bpm);
// 	}
// 	return 0;
// }


