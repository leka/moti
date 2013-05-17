#ifndef RGBLED_H
#define RGBLED_H

#include "Arduino.h" 

class RGBLED 	{
  public:
    RGBLED(uint8_t  redPin, uint8_t  greenPin, uint8_t  bluePin);
	RGBLED();
	void InitPins();
	//void colorRGB(int red, int green, int blue);
	void colorRGB(int, int, int);
	void colorHSV(int hue, int Value, int Saturation);
  private:
	uint8_t  Pin_red;
	uint8_t  Pin_green;
	uint8_t  Pin_blue; 
};

#endif

