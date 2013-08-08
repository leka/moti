#include <Arduino.h>
#include <Led.h>


/**
 * @file Led.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


// CONSTRUCTORS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief Led Class Constructor
 *
 * @param redPin Red pin
 * @param greenPin Green pin
 * @param bluePin Blue pin
 */
Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){
	this -> redPin   = redPin;
	this -> greenPin = greenPin;
	this -> bluePin  = bluePin;
}

/**
 * @brief Led Class Constructor
 */
Led::Led(){
	this -> redPin   = DEFAULT_RED_PIN;
	this -> greenPin = DEFAULT_GREEN_PIN;
	this -> bluePin  = DEFAULT_BLUE_PIN;
}

void Led::init(){
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;

	rgbBuffer[0] = 0;
	rgbBuffer[1] = 0;
	rgbBuffer[2] = 0;
}




// GENERAL METHODS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Method used to set the value of red, green or blue
 * @param index 0, 1 or 2 for red, green or blue.
 * @param value value for the corresponding led. It must be between 0-255
 */
void Led::setRgb(int8_t index, int value){
	index = constrain(index, 0, 2);
	rgb[index] = constrain(value, 0, getLedMaxBrightness());
}

/**
 * @brief Method used to set red, green and blue all at once
 * @param redValue   the red led value, must be between 0-255
 * @param greenValue the green led value, must be between 0-255
 * @param blueValue  the blue led value, must be between 0-255
 */
void Led::setRgb(int redValue, int greenValue, int blueValue){
	rgb[0] = constrain(redValue, 0, getLedMaxBrightness());
	rgb[1] = constrain(greenValue, 0, getLedMaxBrightness());
	rgb[2] = constrain(blueValue, 0, getLedMaxBrightness());
}

/**
 * @brief Method used to set the red led value
 * @param value value for the red led. It must be between 0-255
 */
void Led::setRed(int value){
	rgb[0] = constrain(value, 0, getLedMaxBrightness());
}

/**
 * @brief Method used to set the green led value
 * @param value value for the green led. It must be between 0-255
 */
void Led::setGreen(int value){
	rgb[1] = constrain(value, 0, getLedMaxBrightness());
}

/**
 * @brief Method used to set the blue led value
 * @param value value for the blue led. It must be between 0-255
 */
void Led::setBlue(int value){
	rgb[2] = constrain(value, 0, getLedMaxBrightness());
}

/**
 * @brief Getter method to get the value of red, green or blue
 * @param  index 0, 1 or 2 for red, green or blue.
 * @return       returns the corresponding value, an uint8_t between 0-255
 */
uint8_t Led::getRgb(uint8_t index){
	return rgb[index];
}

/**
 * @brief Getter method for the red value
 * @return returns the red value, an uint8_t between 0-255
 */
uint8_t Led::getRed(){
	return rgb[0];
}

/**
 * @brief Getter method for the red value
 * @return returns the red value, an uint8_t between 0-255
 */
uint8_t Led::getGreen(){
	return rgb[1];
}

/**
 * @brief Getter method for the blue value
 * @return returns the blue value, an uint8_t between 0-255
 */
uint8_t Led::getBlue(){
	return rgb[2];
}

/**
 * @brief Outputs the rgb[] values with the RGB Led
 */
void Led::printRgb(){
	analogWrite(redPin, rgb[0]);
	analogWrite(greenPin, rgb[1]);
	analogWrite(bluePin, rgb[2]);
}

void Led::printRgb(ColorName color){
	colorSwitcher(color);
	printRgb();
}

/**
 * @brief Outputs the rgb[] values with the RGB Led
 *
 * @param redValue red value to output
 * @param greenValue green value to output
 * @param blueValue blue value to output
 */
void Led::printRgb(int redValue, int greenValue, int blueValue){
	rgb[0] = constrain(redValue, 0, getLedMaxBrightness());
	rgb[1] = constrain(greenValue, 0, getLedMaxBrightness());
	rgb[2] = constrain(blueValue, 0, getLedMaxBrightness());

	printRgb();
}

/**
 * @brief Blinks the led with a certain color, a certain number of time with
 * certain delay between blinks
 *
 * @param color the name of the color from enum ColorName{}
 * @param numberOfBlinks number of blinks
 * @param timeBtwBlink delay between each blinks - a good value is 50
 */
void Led::blinkLed(ColorName color, int numberOfBlinks, int timeBtwBlink){
	for(int i = 0 ; i < numberOfBlinks ; i++) {
		colorSwitcher(color);
		printRgb();
		delay(timeBtwBlink);
		printRgb(0, 0, 0);
		delay(timeBtwBlink);
	}
}

/**
 * @brief Blinks the led with a certain value of red/green/blue, a certain
 * number of time with certain delay between blinks
 *
 * @param red red value to output
 * @param green green value to output
 * @param blue blue value to output
 * @param numberOfBlinks number of blinks
 * @param timeBtwBlink delay between each blinks - a good value is 50
 */
void Led::blinkLed(int red, int green, int blue, int numberOfBlinks, int timeBtwBlink){
	for(int i = 0 ; i < numberOfBlinks ; i++) {
		printRgb(red, green, blue);
		delay(timeBtwBlink);
		printRgb(0, 0, 0);
		delay(timeBtwBlink);
	}
}

/**
 * @brief Fades the led to a certain color
 *
 * @param color the name of the color from enum ColorName{}
 */
void Led::fadeLedTo(ColorName color){
	int fadeRed = 0;
	int fadeGreen = 0;
	int fadeBlue = 0;

	setRgb(0, 0, 0);

	colorSwitcher(color);

	while(fadeRed <= rgb[0] || fadeGreen <= rgb[1] || fadeBlue <= rgb[2]){
		colorSwitcher(color);
		if (fadeRed < rgb[0]){
			fadeRed+=3;
		}
		if (fadeGreen < rgb[1]){
			fadeGreen+=3;
		}
		if (fadeBlue < rgb[2]){
			fadeBlue+=3;
		}
		printRgb(fadeRed, fadeGreen, fadeBlue);
	}
}

/**
 * @brief Turns led ON - white color.
 */
void Led::turnLedOn(){
	printRgb(255, 255, 255);
}

/**
 * @brief Turns led OFF.
 */
void Led::turnLedOff(){
	printRgb(0, 0, 0);
}

/**
 * @brief Color switcher used to get rgb[] values of different colors by their
 * name such as RED, GREEN, BLUE, etc.
 *
 * @param color the name of the color from enum ColorName{}
 */
void Led::colorSwitcher(ColorName color){
	switch(color){
		case DARK_RED:
			rgb[0] = 186;
			rgb[1] = 48;
			rgb[2] = 42;
			break;

		case RED:
			rgb[0] = 221;
			rgb[1] = 60;
			rgb[2] = 48;
			break;

		case LIGHT_RED:
			rgb[0] = 222;
			rgb[1] = 63;
			rgb[2] = 89;
			break;

		case PURPLE:
			rgb[0] = 165;
			rgb[1] = 67;
			rgb[2] = 188;
			break;

		case BLUE:
			rgb[0] = 41;
			rgb[1] = 133;
			rgb[2] = 220;
			break;

		case LIGHT_BLUE:
			rgb[0] = 95;
			rgb[1] = 184;
			rgb[2] = 224;
			break;

		case WHITE:
			rgb[0] = 248;
			rgb[1] = 253;
			rgb[2] = 253;
			break;

		case LIGHT_PINK:
			rgb[0] = 255;
			rgb[1] = 232;
			rgb[2] = 225;
			break;

		case YELLOW:
			rgb[0] = 250;
			rgb[1] = 211;
			rgb[2] = 51;
			break;

		case DARK_YELLOW:
			rgb[0] = 244;
			rgb[1] = 174;
			rgb[2] = 51;
			break;

		case ORANGE:
			rgb[0] = 240;
			rgb[1] = 143;
			rgb[2] = 51;
			break;

		case DARK_ORANGE:
			rgb[0] = 239;
			rgb[1] = 134;
			rgb[2] = 59;
			break;

		case LIGHT_GREEN:
			rgb[0] = 216;
			rgb[1] = 255;
			rgb[2] = 56;
			break;

		case GREEN:
			rgb[0] = 98;
			rgb[1] = 163;
			rgb[2] = 75;
			break;

		case RAND:
			rgb[0] = random(0, 255);
			rgb[1] = random(0, 255);
			rgb[2] = random(0, 255);
			break;

		default:
			rgb[0] = random(0, 255);
			rgb[1] = random(0, 255);
			rgb[2] = random(0, 255);
			break;
	}

}




// CONSTANTS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Setter method for _ledMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getLedMaxBrightness()
 * @param value the value you want to assign to _ledMaxBrightness.
 */
void Led::setLedMaxBrightness(int value){
	_ledMaxBrightness = value;
}

/**
 * @brief Setter method for _redMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getRedMaxBrightness()
 * @param value the value you want to assign to _redMaxBrightness.
 */
void Led::setRedMaxBrightness(int value){
	_redMaxBrightness = value;
}

/**
 * @brief Setter method for _greenMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getGreenMaxBrightness()
 * @param value the value you want to assign to _greenMaxBrightness.
 */
void Led::setGreenMaxBrightness(int value){
	_greenMaxBrightness = value;
}

/**
 * @brief Setter method for _blueMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getBlueMaxBrightness()
 * @param value the value you want to assign to _blueMaxBrightness.
 */
void Led::setBlueMaxBrightness(int value){
	_blueMaxBrightness = value;
}

/**
 * @brief Getter method for _ledMaxBrightness
 *
 * It is used to get the maximum brightness of the led.
 * @return the value of _ledMaxBrightness
 */
int Led::getLedMaxBrightness(){
	return _ledMaxBrightness;
}

/**
 * @brief Getter method for _redMaxBrightness
 *
 * It is used to get the maximum brightness of the red led.
 * @return the value of _redMaxBrightness
 */
int Led::getRedMaxBrightness(){
	return _redMaxBrightness;
}

/**
 * @brief Getter method for _greenMaxBrightness
 *
 * It is used to get the maximum brightness of the green led.
 * @return the value of _greenMaxBrightness
 */
int Led::getGreenMaxBrightness(){
	return _greenMaxBrightness;
}

/**
 * @brief Getter method for _blueMaxBrightness
 *
 * It is used to get the maximum brightness of the blue led.
 * @return the value of _blueMaxBrightness
 */
int Led::getBlueMaxBrightness(){
	return _blueMaxBrightness;
}

/**
 * @brief Reset method for _ledMaxBrightness to initial value
 */
void Led::resetLedMaxBrightness(){
	_ledMaxBrightness = DEFAULT_LED_MAX_BRIGHTNESS;
}

/**
 * @brief Reset method for _redMaxBrightness to initial value
 */
void Led::resetRedMaxBrightness(){
	_redMaxBrightness = DEFAULT_RED_MAX_BRIGHTNESS;
}

/**
 * @brief Reset method for _greenMaxBrightness to initial value
 */
void Led::resetGreenMaxBrightness(){
	_greenMaxBrightness = DEFAULT_GREEN_MAX_BRIGHTNESS;
}

/**
 * @brief Reset method for _blueMaxBrightness to initial value
 */
void Led::resetBlueMaxBrightness(){
	_blueMaxBrightness = DEFAULT_BLUE_MAX_BRIGHTNESS;
}