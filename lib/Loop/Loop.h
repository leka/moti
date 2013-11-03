#ifndef LEKA_MOTI_ARDUINO_Loop_H_
#define LEKA_MOTI_ARDUINO_Loop_H_

/**
 * @file Loop.h
 * @brief Loop takes care of all the time related issues
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>

namespace Loop {

	void init();

	void setLoopDelay(int value);
	void setSleepDelay(int value);

	int getLoopDelay();
	int getSleepDelay();

	void resetLoopDelay();
	void resetSleepDelay();	

	bool delay(uint64_t delay);
	bool delay(uint64_t delay, uint64_t delta);

	//	Variables
	uint16_t _loopDelay;
	uint16_t _sleepDelay;
	uint16_t _awakeThreshold;
	uint16_t _deltaAccelThreshold;
	uint16_t _highActivityThreshold;

	//	Constants
	static const uint8_t DEFAULT_LOOP_DELAY              = 75;
	static const uint8_t DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;
	static const uint16_t DEFAULT_SLEEP_DELAY            = 600;
	static const uint16_t DEFAULT_AWAKE_THRESHOLD        = 300;
	static const uint16_t DEFAULT_DELTA_ACCEL_THRESHOLD  = 200;
}

#endif