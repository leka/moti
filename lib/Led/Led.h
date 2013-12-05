#ifndef LEKA_MOTI_ARDUINO_LED_H_
#define LEKA_MOTI_ARDUINO_LED_H_

/**
 * @file Led.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include "ChibiOS_AVR.h"

enum ColorName {
		DARK_RED, RED, LIGHT_RED, PURPLE, BLUE, LIGHT_BLUE, WHITE, LIGHT_PINK, YELLOW, DARK_YELLOW, ORANGE, DARK_ORANGE, LIGHT_GREEN, GREEN, RAND
	};


/**
 * @class Led
 * @brief Led class gathers all the LED functions for Moti.
 */
class Led {

	public:

		Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

		Led();

		//	LED
		void colorSwitcher(ColorName color);

		void setRgb(uint8_t index, uint8_t value);
		void setRgb(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

		uint8_t getRgb(uint8_t index) const;

		void shine() const;
		void shine(ColorName color);
		void shine(uint8_t red, uint8_t green, uint8_t blue);

		void turnOff();

	private:

		//	VARIABLES
		uint8_t _RGB[3], _tmpRGB[3];

		uint8_t _redPin;
		uint8_t _greenPin;
		uint8_t _bluePin;

		//	MUTEXES
		MUTEX_DECL(rgbValuesMutex);

		//	CONSTANTS
		static const uint8_t DEFAULT_LED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_RED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
		static const uint8_t DEFAULT_BLUE_MAX_BRIGHTNESS  = 255;
};

#endif