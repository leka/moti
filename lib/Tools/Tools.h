#ifndef TOOLS_H_
#define TOOLS_H_

/**
 * @file Tools.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <stdio.h>

//	Methods
int8_t sabs8(int8_t i);
int16_t sabs16(int16_t i);
int32_t sabs32(int32_t i);

//	Constants
static const int8_t INT8_MIN = -128;
static const int8_t INT8_MAX = 127;
static const int16_t INT16_MIN = -32768;
static const int16_t INT16_MAX = 32767;
static const int32_t INT32_MIN = -2147483647;
static const int32_t INT32_MAX = 2147483647;



#endif