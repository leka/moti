void checkSensors() {
	//	this function checks the sensors at the beginning of the void loop().

	AccelGyro.getValues(XYZ);

	deltaXYZ[0] = abs(XYZ[0] - lastXYZ[0]);
	deltaXYZ[1] = abs(XYZ[1] - lastXYZ[1]);
	deltaXYZ[2] = abs(XYZ[2] - lastXYZ[2]);
}