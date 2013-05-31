//##########################################################################//
//	THIS FILE CONTAINS ALL OF THE FUNCTIONS USED IN moti_X.ino				//
//	THE PURPOSE OF THIS FILE IS TO SIMPLIFY THE READING AND UNDERSTANDING	//
//	OF THE MAIN PROGRAM.													//
//	THE CODE WRITTEN IN function.ino MUST BE OVERLY COMMENTED!				//
//##########################################################################//

void setAllToZero(){

	setMotorPinToZero();
	setMotorValueToZero();
	setMotorSpeedAndDirection();

	setRGBValueToZero();
	setLedPinToZero();
}

boolean shutDown() {
	//	this function only returns isShutDown as true.
	//	it is then used in an if statement during which the robot to wake up.

	setAllToZero();

	return isShutDown = true;
}



void softwareReset() {
	//	this function reset the program so that it can restart before the void setup().
	//	it is used because we don't know how much time has passed since the last awaken state.
	//	the environment may have change, so going through the void setup() again is required.

	asm volatile ("  jmp 0");
}



