void sendSerialFeedback() {
	//	this function serial prints the state of different variables.
	//	it can be really usefull to debug and/or calibrate the robot.

	Serial.print(F("Sleep: "));
	Serial.print(sleepy);

	Serial.print(F("R: "));
	Serial.print(RGB[0]);
	Serial.print(F(" G: "));
	Serial.print(RGB[1]);
	Serial.print(F(" B: "));
	Serial.print(RGB[2]);

	Serial.print(F(" | MOTOR 1: "));
	Serial.print(MOTOR[0]);
	Serial.print(F(" MOTOR 2: "));
	Serial.print(MOTOR[1]);

	Serial.print(F(" | X: "));
	Serial.print(XYZ[0]);
	Serial.print(F(" Y: "));
	Serial.print(XYZ[1]);
	Serial.print(F(" Z: "));
	Serial.print(XYZ[2]);

	Serial.print(F(" | dX: "));
	Serial.print(deltaXYZ[0]);
	Serial.print(F(" dY: "));
	Serial.print(deltaXYZ[1]);
	Serial.print(F(" dZ: "));
	Serial.println(deltaXYZ[2]);
}



void sendProcessingFeedback() {
	//	this function uses the serial to communicate with the Processing app in order to display Moti's mood on the computer screen.
	//	it can be really usefull to debug and/or calibrate the robot, check the sensors, make some machine learning and just to look awesome during a presentation :)

	Serial.print(XYZ[0]);
	Serial.print(',');
	Serial.print(XYZ[1]);
	Serial.print(',');
	Serial.print(XYZ[2]);

	Serial.print(',');

	Serial.print(deltaXYZ[0]);
	Serial.print(',');
	Serial.print(deltaXYZ[1]);
	Serial.print(',');
	Serial.print(deltaXYZ[2]);

	Serial.print(',');

	Serial.print(RGB[0]);
	Serial.print(',');
	Serial.print(RGB[1]);
	Serial.print(',');
	Serial.print(RGB[2]);

	Serial.print(',');

	Serial.println(MOTOR[1]);
}



void sendJSON(){
	Serial.print(F('{'));

		Serial.print(F('"accelerometer" : '));

		Serial.print(F('{'))

			Serial.print(F('"x" : "'));
			Serial.print(XYZ[0]);
			Serial.print(F('",'));

			Serial.print(F('"y" : "'));
			Serial.print(XYZ[1]);
			Serial.print(F('",'));

			Serial.print(F('"z" : "'));
			Serial.print(XYZ[2]);
			Serial.print(F('"');

		Serial.print(F(' }'));

		Serial.print(F('"gyroscope" : '));

		Serial.print(F('{'))

			Serial.print(F('"yaw" : "'));
			Serial.print(XYZ[3]);
			Serial.print(F('",'));

			Serial.print(F('"pitch" : "'));
			Serial.print(XYZ[4]);
			Serial.print(F('",'));

			Serial.print(F('"roll" : "'));
			Serial.print(XYZ[5]);
			Serial.print(F('"');

		Serial.print(F(' }'));

	Serial.println(F('}'));
}

