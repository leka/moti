#include "Tools.h"


/* Safe 8 bit absolute function */
int8_t sabs8(int8_t i){
    int8_t absValue;

    if (INT8_MIN == i) {
        absValue = INT8_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}

/* Safe 16 bit absolute function */
int16_t sabs16(int16_t i)
{
    int16_t absValue;

    if (INT16_MIN == i) {
        absValue = INT16_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}

/* Safe 32 bit absolute function */
int32_t sabs32(int32_t i)
{
    int32_t absValue;

    if (INT32_MIN == i) {
        absValue = INT32_MAX;
    }
    else {
        absValue = i < 0 ? -i : i;
    }

    return absValue;
}