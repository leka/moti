#include <Arduino.h>
#include <Sensors.h>

/**
 * @file Sensors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


// CONSTRUCTORS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Sensors Class Constructor
 */
Sensors::Sensors(){
}

void Sensors::init(){
	for(int i = 0 ; i < 3 ; i++){
		XYZ[i] = 0;
		lastXYZ[i] = 0;
		deltaXYZ[i] = 0;
		YPR[i] = 0;
		lastYPR[i] = 0;
		deltaYPR[i] = 0;
	}

	delay(500);
	Wire.begin();
	AccelGyro.init();
	Wire.begin();
	delay(50);
	AccelGyro.init();
}


// GENERAL FUNCTIONS //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checking accelerometer and gyroscope
 *
 * checkSensors() is used to check the accelerometer and the gyroscope. It calls two other functions: checkAccelerometer() and checkGyroscope().
 * Values can be accessed with getXYZ(uint8_t i) and getYPR(uint8_t i)
 */
void Sensors::checkSensors(){
	checkAccelerometer();
	checkGyroscope();
}

/**
 * @brief Checking accelerometer
 *
 * checkAccelerometer() is used to check the accelerometer. It calls FreeSixIMU#getRawValues().
 * Values can be accessed with getXYZ(uint8_t index).
 */
void Sensors::checkAccelerometer(){
	AccelGyro.getRawValues(XYZ);
}

/**
 * @brief Checking gyroscope
 *
 * checkGyroscope() is used to check the gyroscope. It calls FreeSixIMU#getYawPitchRoll().
 * Values can be accessed with getYPR(uint8_t index).
 */
void Sensors::checkGyroscope(){
	float tmpYPR[3];
	AccelGyro.getYawPitchRoll(tmpYPR);
	YPR[0] = (int) tmpYPR[0];
	YPR[1] = (int) tmpYPR[1];
	YPR[2] = (int) tmpYPR[2];
}

/**
 * @brief Send data formated as a JSON string
 *
 * sendJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void Sensors::sendJson(){
	String json;

	json = "{\"accel\":{\"x\":";
	json = json + getXYZ(0);
	json = json + ",\"y\":";
	json = json + getXYZ(1);
	json = json + ",\"z\":";
	json = json + getXYZ(2);
	json = json + "},\"gyro\":{\"yaw\":";
	json = json + getYPR(0);
	json = json + ",\"pitch\":";
	json = json + getYPR(1);
	json = json + ",\"roll\":";
	json = json + getYPR(2);
	json = json + "}}";

	Serial.println(json);
}

/**
 * @brief Accessing X, Y, Z acceleration
 *
 * getXYZ() is used to access the acceleration values of X, Y and Z.
 * @param index index of the value you want to access: 0 -> X || 1 -> Y || 2 -> Z
 * @return acceleration for X, Y or Z
 */
int Sensors::getXYZ(uint8_t index){
	return XYZ[index];
}

/**
 * @brief Accessing Yaw, Pitch, Roll angles
 *
 * getXYZ() is used to access the angle values of Yaw, Pitch and Roll
 * @param index index of the value you want to access: 0 -> Y || 1 -> P || 2 -> R
 * @return angle of Y, P, R
 */
int Sensors::getYPR(uint8_t index){
	return YPR[index];
}

/**
 * @brief Calculate the delta between the present and the past values
 *
 * computeSensorValues() is used compute the delta between the present and the past values of the acceleration and yaw/pitch/roll.
 * Then, it can be accessed with getDeltaXYZ() or getDeltaYPR().
 */
void Sensors::computeDelta(){
	deltaXYZ[0] = XYZ[0] - lastXYZ[0];
	deltaXYZ[1] = XYZ[1] - lastXYZ[1];
	deltaXYZ[2] = XYZ[2] - lastXYZ[2];

	deltaYPR[0] = YPR[0] - lastYPR[0];
	deltaYPR[1] = YPR[1] - lastYPR[1];
	deltaYPR[2] = YPR[2] - lastYPR[2];
}

/**
 * @brief Update last sensor values with present values
 *
 * updateLastSensorValues() saves the last sensors values for computeSensorValues().
 * The values can be accessed using getLastXYZ() and getLastYPR().
 */
void Sensors::updateLastValues(){
	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	lastYPR[0] = YPR[0];
	lastYPR[1] = YPR[1];
	lastYPR[2] = YPR[2];
}