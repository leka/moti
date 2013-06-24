#include "Moti.h"
#include "Arduino.h"

//#####//
// LED //
//#####//

void Moti::setRgbValue(){
	rgbBuffer[0] = constrain(rgb[0], 0, getLedMaxBrightness());
	rgbBuffer[1] = constrain(rgb[1], 0, getLedMaxBrightness());
	rgbBuffer[2] = constrain(rgb[2], 0, getLedMaxBrightness());

	rgb[0] = rgbBuffer[0];
	rgb[1] = rgbBuffer[1];
	rgb[2] = rgbBuffer[2];
}

void Moti::setRgbValue(int value){
	for(int _i = 0 ; _i < 3 ; _i++){
		rgbBuffer[_i] = constrain(value, 0, getLedMaxBrightness());
		rgb[_i] = rgbBuffer[_i];
	}
}

void Moti::setRgbValue(int redValue, int greenValue, int blueValue){
	rgbBuffer[0] = constrain(redValue, 0, getLedMaxBrightness());
	rgbBuffer[1] = constrain(greenValue, 0, getLedMaxBrightness());
	rgbBuffer[2] = constrain(blueValue, 0, getLedMaxBrightness());

	rgb[0] = rgbBuffer[0];
	rgb[1] = rgbBuffer[1];
	rgb[2] = rgbBuffer[2];
}

void Moti::printRgbColor(){
	rgbled.colorRGB(rgb[0], rgb[1], rgb[2]);
}

void Moti::printRgbColor(int redValue, int greenValue, int blueValue){
	redValue   = constrain(redValue, 0, getLedMaxBrightness());
	greenValue = constrain(greenValue, 0, getLedMaxBrightness());
	blueValue  = constrain(blueValue, 0, getLedMaxBrightness());

	rgbled.colorRGB(redValue, greenValue, blueValue);
}

void Moti::blinkLed(int nbrOfBlinks){
	int _timeBtwBlink = 50;
	int _nbrOfBlinks = nbrOfBlinks;
	int _iBlink;

	for(_iBlink = 0 ; _iBlink < _nbrOfBlinks ; _iBlink++) {
		rgbled.colorRGB(255, 255, 255);

		delay(_timeBtwBlink);

		rgbled.colorRGB(0, 0, 0);

		delay(_timeBtwBlink);
	}
}

void Moti::fadeLedTo(char * colorName){
	int fadeRed = 0;
	int fadeGreen = 0;
	int fadeBlue = 0;
	while(fadeRed <= Moti::rgb[0] || fadeGreen <= Moti::rgb[1] || fadeBlue <= Moti::rgb[2]){
		if (fadeRed < Moti::rgb[0]){
			fadeRed++;
		}
		if (fadeGreen < Moti::rgb[1]){
			fadeGreen++;
		}
		if (fadeBlue < Moti::rgb[2]){
			fadeBlue++;
		}
		printRgbColor();
	}
}

void Moti::turnLedOn(){
	rgbled.colorRGB(255, 255, 255);
}

void Moti::turnLedOff(){
	rgbled.colorRGB(0, 0, 0);
}

