#ifndef LEKA_ARDUINO_ROBOT_MOTI_LED_H_
#define LEKA_ARDUINO_ROBOT_MOTI_LED_H_

/**
 * @file MotiLED.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include "Arduino.h"

enum ColorName {
			DARK_RED, RED, LIGHT_RED, PURPLE, BLUE, LIGHT_BLUE, WHITE, LIGHT_PINK, YELLOW, DARK_YELLOW, ORANGE, DARK_ORANGE, LIGHT_GREEN, GREEN, RAND
	};


/**
 * @class MotiLED
 * @brief MotiLED class gathers all the LED functions for Moti.
 */
class MotiLED {

	public:

		MotiLED(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

		MotiLED();

		//	SET CONSTANTS
		void setLedMaxBrightness(int value);
		void setRedMaxBrightness(int value);
		void setGreenMaxBrightness(int value);
		void setBlueMaxBrightness(int value);


		//	GET CONSTANTS
		int getLedMaxBrightness();
		int getRedMaxBrightness();
		int getGreenMaxBrightness();
		int getBlueMaxBrightness();


    	//	RESET CONSTANTS
		void resetLedMaxBrightness();
		void resetRedMaxBrightness();
		void resetGreenMaxBrightness();
		void resetBlueMaxBrightness();


		//	LED
		void initializeLed();

		void colorSwitcher(ColorName color);

		void setRgbValue(int8_t index, int value);
		void setRed(int value);
		void setGreen(int value);
		void setBlue(int value);
		void setRgbValue(int redValue, int greenValue, int blueValue);

		uint8_t getRgbValue(uint8_t index);
		uint8_t getRed();
		uint8_t getGreen();
		uint8_t getBlue();

		void printRgbColor();
		void printRgbColor(ColorName color);
		void printRgbColor(int red, int green, int blue);

		void blinkLed(ColorName color, int numberOfBlinks, int timeBtwBlink);
		void blinkLed(int red, int green, int blue, int numberOfBlinks, int timeBtwBlink);

		void fadeLedTo(ColorName color);

		void turnLedOff();
		void turnLedOn();


	private:

		//	VARIABLES
		int16_t rgb[3], rgbBuffer[3];

		uint8_t redPin;
		uint8_t greenPin;
		uint8_t bluePin;

		uint8_t _ledMaxBrightness;
		uint8_t _redMaxBrightness;
		uint8_t _greenMaxBrightness;
		uint8_t _blueMaxBrightness;


		//	CONSTANTS
		static const uint8_t DEFAULT_LED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_RED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
		static const uint8_t DEFAULT_BLUE_MAX_BRIGHTNESS  = 255;


		//	DEFAULT LED PINS
		static const uint8_t DEFAULT_RED_PIN   = 9;
		static const uint8_t DEFAULT_GREEN_PIN = 10;
		static const uint8_t DEFAULT_BLUE_PIN  = 11;
};

#endif