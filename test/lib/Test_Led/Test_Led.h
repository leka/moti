#ifndef LEKA_MOTI_ARDUINO_TEST_LED_H_
#define LEKA_MOTI_ARDUINO_TEST_LED_H_

/**
 * @file Led.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Led.h>

class TEST_LED {
	
	public:

		TEST_LED();

		void test_constant_set_get(Led& led);
		void test_led_set_get(Led& led);
		void test_led_output(Led& led);
		void test_led_blink(Led& led);

};

#endif