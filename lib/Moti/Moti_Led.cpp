#include "Moti.h"
#include "Arduino.h"

//#####//
// LED //
//#####//

void MOTI::initializeLed(){
	rgb[0]       = 0;
	rgb[1]       = 0;
	rgb[2]       = 0;
	rgbBuffer[0] = 0;
	rgbBuffer[1] = 0;
	rgbBuffer[2] = 0;
}

void MOTI::setRgbValue(int8_t index, int value){
	index = constrain(index, 0, 2);
	rgb[index] = constrain(value, 0, getLedMaxBrightness());
}

void MOTI::setRed(int value){
	rgb[0] = constrain(value, 0, getLedMaxBrightness());
}

void MOTI::setGreen(int value){
	rgb[1] = constrain(value, 0, getLedMaxBrightness());
}

void MOTI::setBlue(int value){
	rgb[2] = constrain(value, 0, getLedMaxBrightness());
}

void MOTI::setRgbValue(int redValue, int greenValue, int blueValue){
	rgb[0] = constrain(redValue, 0, getLedMaxBrightness());
	rgb[1] = constrain(greenValue, 0, getLedMaxBrightness());
	rgb[2] = constrain(blueValue, 0, getLedMaxBrightness());
}

uint8_t MOTI::getRgbValue(uint8_t index){
	return rgb[index];
}

uint8_t MOTI::getRed(){
	return rgb[0];
}

uint8_t MOTI::getGreen(){
	return rgb[1];
}

uint8_t MOTI::getBlue(){
	return rgb[2];
}

void MOTI::printRgbColor(){
	rgbled.colorRGB(rgb[0], rgb[1], rgb[2]);
}

void MOTI::printRgbColor(String colorName){
	colorSwitcher(colorName);
	printRgbColor();
}

void MOTI::printRgbColor(int redValue, int greenValue, int blueValue){
	rgb[0] = constrain(redValue, 0, getLedMaxBrightness());
	rgb[1] = constrain(greenValue, 0, getLedMaxBrightness());
	rgb[2] = constrain(blueValue, 0, getLedMaxBrightness());

	printRgbColor();
}

void MOTI::blinkLed(String colorName, int numberOfBlinks, int timeBtwBlink){
	for(int i = 0 ; i < numberOfBlinks ; i++) {
		colorSwitcher(colorName);
		printRgbColor();
		delay(timeBtwBlink);
		printRgbColor(0, 0, 0);
		delay(timeBtwBlink);
	}
}

void MOTI::blinkLed(int red, int green, int blue, int numberOfBlinks, int timeBtwBlink){
	for(int i = 0 ; i < numberOfBlinks ; i++) {
		printRgbColor(red, green, blue);
		delay(timeBtwBlink);
		printRgbColor(0, 0, 0);
		delay(timeBtwBlink);
	}
}

void MOTI::fadeLedTo(String colorName){
	int fadeRed = 0;
	int fadeGreen = 0;
	int fadeBlue = 0;

	initializeLed();

	colorSwitcher(colorName);

	while(fadeRed <= rgb[0] || fadeGreen <= rgb[1] || fadeBlue <= rgb[2]){
		if (fadeRed < rgb[0]){
			fadeRed+=3;
		}
		if (fadeGreen < rgb[1]){
			fadeGreen+=3;
		}
		if (fadeBlue < rgb[2]){
			fadeBlue+=3;
		}
		printRgbColor(fadeRed, fadeGreen, fadeBlue);
	}
}

void MOTI::turnLedOn(){
	printRgbColor(255, 255, 255);
}

void MOTI::turnLedOff(){
	printRgbColor(0, 0, 0);
}

void MOTI::colorSwitcher(String colorName){
	if(colorName == "dark red"){
		rgb[0] = 186;
		rgb[1] = 48;
		rgb[2] = 42;
	}
	else if(colorName == "red"){
		rgb[0] = 221;
		rgb[1] = 60;
		rgb[2] = 48;
	}
	else if(colorName == "pink"){
		rgb[0] = 222;
		rgb[1] = 63;
		rgb[2] = 89;
	}
	else if(colorName == "purple"){
		rgb[0] = 165;
		rgb[1] = 67;
		rgb[2] = 188;
	}
	else if(colorName == "blue"){
		rgb[0] = 41;
		rgb[1] = 133;
		rgb[2] = 220;
	}
	else if(colorName == "light blue"){
		rgb[0] = 95;
		rgb[1] = 184;
		rgb[2] = 224;
	}
	else if(colorName == "white"){
		rgb[0] = 248;
		rgb[1] = 253;
		rgb[2] = 253;
	}
	else if(colorName == "light pink"){
		rgb[0] = 255;
		rgb[1] = 232;
		rgb[2] = 225;
	}
	else if(colorName == "yellow"){
		rgb[0] = 250;
		rgb[1] = 211;
		rgb[2] = 51;
	}
	else if(colorName == "dark yellow"){
		rgb[0] = 244;
		rgb[1] = 174;
		rgb[2] = 51;
	}
	else if(colorName == "orange"){
		rgb[0] = 240;
		rgb[1] = 143;
		rgb[2] = 51;
	}
	else if(colorName == "dark orange"){
		rgb[0] = 239;
		rgb[1] = 134;
		rgb[2] = 59;
	}
	else if(colorName == "light green"){
		rgb[0] = 216;
		rgb[1] = 255;
		rgb[2] = 56;
	}
	else if(colorName == "green"){
		rgb[0] = 98;
		rgb[1] = 163;
		rgb[2] = 75;
	}
	else {
		rgb[0] = random(0, 255);
		rgb[1] = random(0, 255);
		rgb[2] = random(0, 255);
	}
}

