void checkSensors() {
	//	this function checks the sensors at the beginning of the void loop().

	AccelGyro.getValues(XYZ);
	AccelGyro.getYawPitchRoll(YPR);

	deltaXYZ[0] = abs(XYZ[0] - lastXYZ[0]);
	deltaXYZ[1] = abs(XYZ[1] - lastXYZ[1]);
	deltaXYZ[2] = abs(XYZ[2] - lastXYZ[2]);

	deltaYPR[0] = abs(YPR[0] - lastYPR[0]);
	deltaYPR[1] = abs(YPR[1] - lastYPR[1]);
	deltaYPR[2] = abs(YPR[2] - lastYPR[2]);
}