void setRgbLed() {
	//	this function is used to constrain and set the led to express the robot's feelings

	//	Constrain the RGB[] values between zero and LED_MAX_BRIGHTNESS
	RGB_BUFFER[0] = constrain(RGB[0], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[1] = constrain(RGB[1], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[2] = constrain(RGB[2], 0, BLUE_LED_MAX);

	//	Set RGB[] to the buffer values
	RGB[0] = RGB_BUFFER[0];
	RGB[1] = RGB_BUFFER[1];
	RGB[2] = RGB_BUFFER[2];

	//	Output the values
	LEDrgb.colorRGB(RGB_BUFFER[0], RGB_BUFFER[1], RGB_BUFFER[2]);
}

void fadeToBlue() {
	//	This function is used in void setup() when the robot wakes up
	//	it does not take any argument and can be used anywhere else

	byte _fadeValue;

	for(_fadeValue = 0 ; _fadeValue < BLUE_LED_MAX; _fadeValue +=1) {
		// LEDrgb.colorRGB(0, 0, _fadeValue);
	}
}


void blinkLED(int nbrOfBlinks) {
	//	this function is used to blink all three colors at the same time.
	//	it takes as an argument the number of blinks you want.

	int _timeBtwBlink = 50;
	int _nbrOfBlinks = nbrOfBlinks;
	int _iBlink;

	for(_iBlink = 0 ; _iBlink < _nbrOfBlinks ; _iBlink++) {
		LEDrgb.colorRGB(255, 255, 255);

		delay(_timeBtwBlink);

		LEDrgb.colorRGB(0, 0, 0);

		delay(_timeBtwBlink);
	}

}
