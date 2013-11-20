#ifndef LEKA_MOTI_ARDUINO_MEMORY_H_
#define LEKA_MOTI_ARDUINO_MEMORY_H_

/**
 * @file Memory.h
 *
 * MemoryFree library based on code posted here:
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
 * Extended by Matthew Murdoch to include walking of the free list.
 *
 * @author Matthew Murdoch
 * @version 1.0
 */

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

int freeMemory();

#ifdef  __cplusplus
	}
#endif

#endif