#include "Moti.h"
#include "Arduino.h"

//#########//
// SENSORS //
//#########//

void MOTI::checkSensors(){
	checkAccelerometer();
	checkGyroscope();
}

void MOTI::checkAccelerometer(){
	AccelGyro.getRawValues(XYZ);
}

void MOTI::checkGyroscope(){
	AccelGyro.getYawPitchRoll(YPR);
}

int MOTI::getXYZ(uint8_t i){
	return XYZ[i];
}

int MOTI::getYPR(uint8_t i){
	return YPR[i];
}

void MOTI::computeSensorValues	(){
	deltaXYZ[0] = XYZ[0] - lastXYZ[0];
	deltaXYZ[1] = XYZ[1] - lastXYZ[1];
	deltaXYZ[2] = XYZ[2] - lastXYZ[2];

	deltaYPR[0] = YPR[0] - lastYPR[0];
	deltaYPR[1] = YPR[1] - lastYPR[1];
	deltaYPR[2] = YPR[2] - lastYPR[2];
}

void MOTI::updateLastSensorValues(){
	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	lastYPR[0] = YPR[0];
	lastYPR[1] = YPR[1];
	lastYPR[2] = YPR[2];
}