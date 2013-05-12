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
	analogWrite(RED_PIN, RGB_BUFFER[0]);
	analogWrite(GREEN_PIN, RGB_BUFFER[1]); 
	analogWrite(BLUE_PIN, RGB_BUFFER[2]);
}



void fadeToBlue() {
	//	This function is used in void setup() when the robot wakes up
	//	it does not take any argument and can be used anywhere else

	for(fadeValue = 0 ; fadeValue < BLUE_LED_MAX; fadeValue +=3) {
		analogWrite(BLUE_PIN, fadeValue);  
		delay(10);                            
	} 
}



void blinkLed(byte nbrOfBlink) {
	//	this function is used to blink all three colors at the same time.
	//	it takes as an argument the number of blinks you want.

	int _timeBtwBlink = 50;
	byte _nbrOfBlink = nbrOfBlink;
	byte _iBlink;

	for(_iBlink = 0 ; _iBlink < _nbrOfBlink ; _iBlink++) {
		digitalWrite(RED_PIN,1);
		digitalWrite(GREEN_PIN,1);
		digitalWrite(BLUE_PIN,1);

		delay(_timeBtwBlink);

		digitalWrite(RED_PIN,0);
		digitalWrite(GREEN_PIN,0);
		digitalWrite(BLUE_PIN,0);

		delay(_timeBtwBlink);
	}
}