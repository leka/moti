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


