#include <Arduino.h>
#include "Sensors.h"

/**
 * @file Sensors.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */


//-----------------------------------------------------//
// CONSTRUCTORS
//-----------------------------------------------------//

/**
 * @brief Sensors Class CONSTRUCTORS
 */
Sensors::Sensors(){
	// nothing to do here
}

void Sensors::init(){
	for(uint8_t i = 0 ; i < 3 ; i++){
		_XYZ[i] = 0;
		_tmpXYZ[i] = 0;
		_YPR[i] = 0;
		_tmpYPR[i] = 0;
	}

	delay(500);
	Wire.begin();
	delay(50);
	AccelGyro.init();
}


//-----------------------------------------------------//
// GENERAL
//-----------------------------------------------------//

/**
 * @brief Checking accelerometer and gyroscope
 *
 * checkSensors() is used to check the accelerometer and the gyroscope. It calls two other functions: checkAccelerometer() and checkGyroscope().
 * Values can be accessed with readXYZ(uint8_t i) and readYPR(uint8_t i)
 */
void Sensors::read(){
	readAccelerometer();
	readGyroscope();
}

/**
 * @brief Checking accelerometer
 *
 * checkAccelerometer() is used to check the accelerometer. It calls FreeSixIMU::getRawValues().
 * Values can be accessed with getXYZ(uint8_t index).
 */
void Sensors::readAccelerometer(){
	AccelGyro.getRawValues(_tmpXYZ);

	chMtxLock(&sensorsDataMutex);
		_XYZ[0] = _tmpXYZ[0];
		_XYZ[1] = _tmpXYZ[1];
		_XYZ[2] = _tmpXYZ[2];
	chMtxUnlock();
}

/**
 * @brief Checking gyroscope
 *
 * checkGyroscope() is used to check the gyroscope. It calls FreeSixIMU#getYawPitchRoll().
 * Values can be accessed with getYPR(uint8_t index).
 */
void Sensors::readGyroscope(){
	AccelGyro.getYawPitchRoll(_tmpYPR);

	chMtxLock(&sensorsDataMutex);
		_YPR[0] = (int) _tmpYPR[0];
		_YPR[1] = (int) _tmpYPR[1];
		_YPR[2] = (int) _tmpYPR[2];
	chMtxUnlock();
}

/**
 * @brief Accessing X, Y, Z acceleration
 *
 * getXYZ() is used to access the acceleration values of X, Y and Z.
 * @param index index of the value you want to access: 0 -> X || 1 -> Y || 2 -> Z
 * @return acceleration for X, Y or Z
 */
int Sensors::readXYZ(uint8_t index) const {
	return _XYZ[index];
}

/**
 * @brief Accessing Yaw, Pitch, Roll angles
 *
 * readXYZ() is used to access the angle values of Yaw, Pitch and Roll
 * @param index index of the value you want to access: 0 -> Y || 1 -> P || 2 -> R
 * @return angle of Y, P, R
 */
int Sensors::readYPR(uint8_t index) const {
	return _YPR[index];
}

/**
 * @brief Send data formated as a JSON string
 *
 * sendJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void Sensors::sendJson() const {
	Serial.print(F("{"));
		Serial.print(F("\"accel\":"));

			Serial.print(F("{"));

				Serial.print(F("\"x\":"));
				Serial.print(_XYZ[0]);
				Serial.print(F(","));

				Serial.print(F("\"y\":"));
				Serial.print(_XYZ[1]);
				Serial.print(F(","));

				Serial.print(F("\"z\":"));
				Serial.print(_XYZ[2]);

			Serial.print(F("},"));

		Serial.print(F("\"gyro\":"));

			Serial.print(F("{"));

				Serial.print(F("\"yaw\":"));
				Serial.print(_YPR[0]);
				Serial.print(F(","));

				Serial.print(F("\"pitch\":"));
				Serial.print(_YPR[1]);
				Serial.print(F(","));

				Serial.print(F("\"roll\":"));
				Serial.print(_YPR[2]);

			Serial.print(F("}"));

	Serial.println(F("}"));
}

/**
 * @brief Send data as binaries
 */
void Sensors::sendData() const {

	sio::writeByte(sio::dataHeader);

	sio::writeByte(sio::numberOfSensors);

	sio::writeByte(sio::accelSensor);
	sio::writeInt(sio::accelData);

	sio::writeInt(readXYZ(0));
	sio::writeInt(readXYZ(1));
	sio::writeInt(readXYZ(2));

	sio::writeByte(sio::gyroSensor);
	sio::writeInt(sio::gyroData);

	sio::writeInt(readYPR(0));
	sio::writeInt(readYPR(1));
	sio::writeInt(readYPR(2));

	sio::writeByte(sio::dataFooter);
}