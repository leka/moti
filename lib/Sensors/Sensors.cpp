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
 * @brief Sensors Class Constructor
 */
Sensors::Sensors(){
}

void Sensors::init(){
	for(uint8_t i = 0 ; i < 3 ; i++){
		XYZ[i] = 0;
		lastXYZ[i] = 0;
		deltaXYZ[i] = 0;
		YPR[i] = 0;
		lastYPR[i] = 0;
		deltaYPR[i] = 0;
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
	AccelGyro.getRawValues(XYZ);
}

/**
 * @brief Checking gyroscope
 *
 * checkGyroscope() is used to check the gyroscope. It calls FreeSixIMU#getYawPitchRoll().
 * Values can be accessed with getYPR(uint8_t index).
 */
void Sensors::readGyroscope(){
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
	Serial.print(F("{"));
		Serial.print(F("\"accel\":"));

			Serial.print(F("{"));

				Serial.print(F("\"x\":"));
				Serial.print(XYZ[0]);
				Serial.print(F(","));

				Serial.print(F("\"y\":"));
				Serial.print(XYZ[1]);
				Serial.print(F(","));

				Serial.print(F("\"z\":"));
				Serial.print(XYZ[2]);

			Serial.print(F("},"));

		Serial.print(F("\"gyro\":"));

			Serial.print(F("{"));

				Serial.print(F("\"yaw\":"));
				Serial.print(YPR[0]);
				Serial.print(F(","));

				Serial.print(F("\"pitch\":"));
				Serial.print(YPR[1]);
				Serial.print(F(","));

				Serial.print(F("\"roll\":"));
				Serial.print(YPR[2]);

			Serial.print(F("}"));

	Serial.println(F("}"));
}

/**
 * @brief Send data as binaries
 */
void Sensors::writeData(){
	read();

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

/**
 * @brief Accessing X, Y, Z acceleration
 *
 * getXYZ() is used to access the acceleration values of X, Y and Z.
 * @param index index of the value you want to access: 0 -> X || 1 -> Y || 2 -> Z
 * @return acceleration for X, Y or Z
 */
int Sensors::readXYZ(uint8_t index){
	return XYZ[index];
}

/**
 * @brief Accessing Yaw, Pitch, Roll angles
 *
 * readXYZ() is used to access the angle values of Yaw, Pitch and Roll
 * @param index index of the value you want to access: 0 -> Y || 1 -> P || 2 -> R
 * @return angle of Y, P, R
 */
int Sensors::readYPR(uint8_t index){
	return YPR[index];
}

/**
 * @brief Calculate the delta between the present and the past values
 *
 * computeSensorValues() is used compute the delta between the present and the past values of the acceleration and yaw/pitch/roll.
 * Then, it can be accessed with readDeltaXYZ() or readDeltaYPR().
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
 * The values can be accessed using readLastXYZ() and readLastYPR().
 */
void Sensors::updateLastValues(){
	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	lastYPR[0] = YPR[0];
	lastYPR[1] = YPR[1];
	lastYPR[2] = YPR[2];
}