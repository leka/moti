void setRGB() {
	//	this function is used to constrain and set the led to express the robot's feelings

	//	Constrain the RGB[] values between zero and LED_MAX_BRIGHTNESS
	RGB_BUFFER[0] = constrain(RGB[0], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[1] = constrain(RGB[1], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[2] = constrain(RGB[2], 0, BLUE_LED_MAX);

	//	Set RGB[] to the buffer values
	RGB[0] = RGB_BUFFER[0];
	RGB[1] = RGB_BUFFER[1];
	RGB[2] = RGB_BUFFER[2];
}

void outputRGB(){
	//	Output the values
	RGBLED.colorRGB(RGB_BUFFER[0], RGB_BUFFER[1], RGB_BUFFER[2]);
}
