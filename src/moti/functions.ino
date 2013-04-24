//##########################################################################//
//	THIS FILE CONTAINS ALL OF THE FUNCTIONS USED IN moti.ino				//
//	THE PURPOSE OF THIS FILE IS TO SIMPLIFY THE READING AND UNDERSTANDING	//
//	OF THE MAIN PROGRAM.													//
//	THE CODE WRITTEN IN function.ino MUST BE OVERLY COMMENTED!				//
//##########################################################################//


void setPinsAsOutput() {
	//	this function sets all the pins to output
	//	it does not take any argument and requires the user to manually write the different pins
	//	possible update: use arguments to set the pins with the less possible code written.

	pinMode(MOTOR_2_DIR, OUTPUT);
	pinMode(MOTOR_1_DIR, OUTPUT);
	pinMode(MOTOR_2_SPEED, OUTPUT);
	pinMode(MOTOR_1_SPEED, OUTPUT);

	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
}



void setPinsValuesToZero() {
	//	this function sets all the pins to zero / LOW
	//	it does not take any argument and requires the user to manually write the different pins
	//	possible update: use arguments to set the pins with the less possible code written.

	digitalWrite(MOTOR_2_DIR, 0);
	digitalWrite(MOTOR_1_DIR, 0);
	digitalWrite(MOTOR_2_SPEED, 0);
	digitalWrite(MOTOR_1_SPEED, 0);

	digitalWrite(RED_PIN, 0);
	digitalWrite(GREEN_PIN, 0);
	digitalWrite(BLUE_PIN, 0);

	analogWrite(RED_PIN, 0);
	analogWrite(GREEN_PIN, 0); 
	analogWrite(BLUE_PIN, 0);
}



void setRgbAndMotorToZero() {

	MOTOR[0] = 0;
	MOTOR[1] = 0;
	MOTOR_BUFFER[0] = 0;
	MOTOR_BUFFER[1] = 0;

	RGB[0] = 0;
	RGB[1] = 0;
	RGB[2] = 0;
}



void checkSensors() {
	//	this function checks the sensors at the beginning of the void loop().

	volume = analogRead(MIC_PIN);
	accel.update();

	deltaVolume = abs(volume - lastVolume);

	XYZ[0] = accel.getX() * 1000;	//	we need to multiply by 1000 to have the decimals. we don't want to use float because it requires more resources to compute.
	XYZ[1] = accel.getY() * 1000;
	XYZ[2] = accel.getZ() * 1000;

	deltaXYZ[0] = abs(XYZ[0] - lastXYZ[0]);
	deltaXYZ[1] = abs(XYZ[1] - lastXYZ[1]);
	deltaXYZ[2] = abs(XYZ[2] - lastXYZ[2]);
}



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



void setMotorSpeedAndDirection() {
	//	this function is used to the motor speed and direction to express the robot's feelings

	MOTOR_BUFFER[0] = constrain(MOTOR[0], -255, 255);  
	MOTOR_BUFFER[1] = constrain(MOTOR[1], -255, 255);

	MOTOR[0]=MOTOR_BUFFER[0];
	MOTOR[1]=MOTOR_BUFFER[1];

	if(MOTOR[0] > 0) {	// Go forward
		digitalWrite(MOTOR_1_DIR, 1);
		analogWrite(MOTOR_1_SPEED, 	abs(MOTOR[0]));
	}
	else {	//	Go backward
		digitalWrite(MOTOR_1_DIR, 0);
		analogWrite(MOTOR_1_SPEED, 	abs(MOTOR[0]));
	}

	if(MOTOR[1] > 0) { // Go forward
		digitalWrite(MOTOR_2_DIR, 1);
		analogWrite(MOTOR_2_SPEED, 	abs(MOTOR[1]));
	}
	else {	//	Go backward
		digitalWrite(MOTOR_2_DIR, 0);
		analogWrite(MOTOR_2_SPEED, 	abs(MOTOR[1]));
	}
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



boolean shutDown() {
	//	this function only returns isShutDown as true.
	//	it is then used in an if statement during which the robot to wake up.

	setPinsValuesToZero();

	return isShutDown = true;
}



void softwareReset() {
	//	this function reset the program so that it can restart before the void setup().
	//	it is used because we don't know how much time has passed since the last awaken state.
	//	the environment may have change, so going through the void setup() again is required.

	asm volatile ("  jmp 0");  
} 



void sendSerialFeedback() {
	//	this function serial prints the state of different variables.
	//	it can be really usefull to debug and/or calibrate the robot.

	Serial.print(F("RED: "));
	Serial.print(RGB[0]);
	Serial.print(F("\t||\tGREEN: "));
	Serial.print(RGB[1]);
	Serial.print(F("\t||\tBLUE: "));
	Serial.print(RGB[2]);

	Serial.print(F("\t||\tMOTOR 1: "));
	Serial.print(MOTOR[0]);
	Serial.print(F("\t||\tMOTOR 2: "));
	Serial.print(MOTOR[1]);

	Serial.print(F("\t||\tSleepy: "));
	Serial.print(sleepy);

	Serial.print(F("\t||\tAccel X: "));
	Serial.print(XYZ[0]);
	Serial.print(F("\t||\tAccel Y: "));
	Serial.print(XYZ[1]);
	Serial.print(F("\t||\tAccel Z: "));
	Serial.print(XYZ[2]);

	Serial.print(F("\t||\tDelta X: "));
	Serial.print(deltaXYZ[0]);
	Serial.print(F("\t||\tDelta Y: "));
	Serial.print(deltaXYZ[1]);
	Serial.print(F("\t||\tDelta Z: "));
	Serial.print(deltaXYZ[2]);

	Serial.print(F("\t||\tVolume: "));
	Serial.print(volume);

	Serial.print(F("\n"));
}


