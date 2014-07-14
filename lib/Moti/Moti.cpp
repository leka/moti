#include "Moti.h"
#include "ChibiOS_AVR.h"

void waitMs(uint16_t ms) {
	chThdSleepMilliseconds(ms);
}