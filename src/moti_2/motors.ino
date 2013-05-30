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