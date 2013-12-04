#include <Arduino.h>
#include <Led.h>


/**
 * @file Led.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

//-----------------------------------------------------//
// CONSTRUCTORS
//-----------------------------------------------------//



/**
 * @brief Led Class Constructor
 */
Led::Led(){
	//nothing to do here
}

/**
 * @brief Led Class Constructor
 *
 * @param redPin Red pin
 * @param greenPin Green pin
 * @param bluePin Blue pin
 */
Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin) {
	_RGB[0] = 0;
	_RGB[1] = 0;
	_RGB[2] = 0;

	_tmpRGB[0] = 0;
	_tmpRGB[1] = 0;
	_tmpRGB[2] = 0;
}

//-----------------------------------------------------//
// GENERAL METHODS
//-----------------------------------------------------//

/**
 * @brief Method used to set the value of red, green or blue
 * @param index 0, 1 or 2 for red, green or blue.
 * @param value value for the corresponding led. It must be between 0-255
 */
void Led::setRgb(int8_t index, int value){
	index = constrain(index, 0, 2);
	_RGB[index] = constrain(value, 0, 255);
}

/**
 * @brief Method used to set red, green and blue all at once
 * @param redValue   the red led value, must be between 0-255
 * @param greenValue the green led value, must be between 0-255
 * @param blueValue  the blue led value, must be between 0-255
 */
void Led::setRgb(int redValue, int greenValue, int blueValue){
	_RGB[0] = constrain(redValue, 0, 255);
	_RGB[1] = constrain(greenValue, 0, 255);
	_RGB[2] = constrain(blueValue, 0, 255);
}

/**
 * @brief Getter method to get the value of red, green or blue
 * @param index 0, 1 or 2 for red, green or blue.
 * @return returns the corresponding value, an uint8_t between 0-255
 */
uint8_t Led::getRgb(uint8_t index) const{
	return _RGB[index];
}

/**
 * @brief Outputs the _RGB[] values with the RGB Led
 */
void Led::shine() const {
	analogWrite(_redPin, _RGB[0]);
	analogWrite(_greenPin, _RGB[1]);
	analogWrite(_bluePin, _RGB[2]);
}

void Led::shine(ColorName color){
	colorSwitcher(color);
	shine();
}

/**
 * @brief Outputs the _RGB[] values with the RGB Led
 *
 * @param redValue red value to output
 * @param greenValue green value to output
 * @param blueValue blue value to output
 */
void Led::shine(int red, int green, int blue){
	_RGB[0] = constrain(red, 0, 255);
	_RGB[1] = constrain(green, 0, 255);
	_RGB[2] = constrain(blue, 0, 255);

	shine();
}

/**
 * @brief Blinks the led with a certain color, a certain number of time without
 * using delay.
 *
 * @param red red value to output
 * @param green green value to output
 * @param blue blue value to output
 * @param numberOfBlinks number of blinks
 * @param timeBtwBlink delay between each blinks - a good value is 50
 */
void Led::blinkSync(int red, int green, int blue, int numberOfBlinks, uint16_t timeBtwBlink){
	for(int i = 0 ; i < numberOfBlinks ; i++) {
		writeRgb(red, green, blue);
		delay(timeBtwBlink);
		writeRgb(0, 0, 0);
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
		writeRgb(fadeRed, fadeGreen, fadeBlue);
	}
}

/**
 * @brief Turns led ON - white color.
 */
void Led::turnOn(){
	writeRgb();
	isOn(true);
}

/**
 * @brief Turns led OFF.
 */
void Led::turnOff(){
	writeRgb(0, 0, 0);
	isOn(false);
	isBlinking(false);
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
			rgb[0] = 255;
			rgb[1] = 0;
			rgb[2] = 0;
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
			rgb[0] = 0;
			rgb[1] = 255;
			rgb[2] = 0;
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



//-----------------------------------------------------//
// CONSTANTS
//-----------------------------------------------------//

/**
 * @brief Setter method for _ledMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling 255
 * @param value the value you want to assign to _ledMaxBrightness.
 */
void Led::setMaxBrightness(int value){
	_ledMaxBrightness = constrain(value, 0, 255);
}

/**
 * @brief Setter method for _redMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getRedMaxBrightness()
 * @param value the value you want to assign to _redMaxBrightness.
 */
void Led::setRedMaxBrightness(int value){
	_redMaxBrightness = constrain(value, 0, 255);
}

/**
 * @brief Setter method for _greenMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getGreenMaxBrightness()
 * @param value the value you want to assign to _greenMaxBrightness.
 */
void Led::setGreenMaxBrightness(int value){
	_greenMaxBrightness = constrain(value, 0, 255);
}

/**
 * @brief Setter method for _blueMaxBrightness
 *
 * Once set, the _sleepDelay can be accessed by calling getBlueMaxBrightness()
 * @param value the value you want to assign to _blueMaxBrightness.
 */
void Led::setBlueMaxBrightness(int value){
	_blueMaxBrightness = constrain(value, 0, 255);
}

/**
 * @brief Getter method for _ledMaxBrightness
 *
 * It is used to get the maximum brightness of the led.
 * @return the value of _ledMaxBrightness
 */
int Led::255{
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
void Led::resetMaxBrightness(){
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