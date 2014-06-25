/*
Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

This file is part of Moti, a spherical robotic smart toy for autistic children.

Moti is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Moti is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Moti. If not, see <http://www.gnu.org/licenses/>.
*/

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
 * Values can be accessed with getXYZ(uint8_t i) and getYPR(uint8_t i)
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
int Sensors::getXYZ(uint8_t index){
	chMtxLock(&sensorsDataMutex);
		int value = _XYZ[index];
	chMtxUnlock();

	return value;
}

/**
 * @brief Accessing Yaw, Pitch, Roll angles
 *
 * getXYZ() is used to access the angle values of Yaw, Pitch and Roll
 * @param index index of the value you want to access: 0 -> Y || 1 -> P || 2 -> R
 * @return angle of Y, P, R
 */
int Sensors::getYPR(uint8_t index){
	chMtxLock(&sensorsDataMutex);
		int value = _YPR[index];
	chMtxUnlock();

	return value;
}

/**
 * @brief Accessing Euler angles
 *
 * getEuler() is used to acces the Euler angles
 * @param index index of the value you want to access: 0 -> Y || 1 -> P || 2 -> R
 * @return angle Psi, Theta or Phi
 */
float Sensors::getEuler(uint8_t index){
	float angles[3];

	AccelGyro.getEuler(angles);

	return angles[index];
}

/**
 * @brief Send sensors data for debug
 */
void Sensors::debug(){
	serial.print(F(" X: "));
	serial.print(getXYZ(0));
	serial.print(F("  Y: "));
	serial.print(getXYZ(1));
	serial.print(F("  Z: "));
	serial.print(getXYZ(2));

	serial.print(F("  ||  "));

	serial.print(F("  Y: "));
	serial.print(getYPR(0));
	serial.print(F("  P: "));
	serial.print(getYPR(1));
	serial.print(F("  R: "));
	serial.println(getYPR(2));

}

/**
 * @brief Send data formated as a JSON string
 *
 * sendJson() is used to interface the robot with other high level languages such as Processing or Javascript.
 * It can also be useful as a debug print out to check the consistency of the sensors.
 */
void Sensors::sendJson(){
	serial.print(F("{"));
		serial.print(F("\"accel\":"));

			serial.print(F("{"));

				serial.print(F("\"x\":"));
				serial.print(getXYZ(0));
				serial.print(F(","));

				serial.print(F("\"y\":"));
				serial.print(getXYZ(1));
				serial.print(F(","));

				serial.print(F("\"z\":"));
				serial.print(getXYZ(2));

			serial.print(F("},"));

		serial.print(F("\"gyro\":"));

			serial.print(F("{"));

				serial.print(F("\"yaw\":"));
				serial.print(getYPR(0));
				serial.print(F(","));

				serial.print(F("\"pitch\":"));
				serial.print(getYPR(1));
				serial.print(F(","));

				serial.print(F("\"roll\":"));
				serial.print(getYPR(2));

			serial.print(F("}"));

	serial.println(F("}"));
}

/**
 * @brief Send data as binaries
 */
void Sensors::sendData(){

	sio::writeByte(sio::dataHeader);

	sio::writeByte(sio::numberOfSensors);

	sio::writeByte(sio::accelSensor);
	sio::writeInt(sio::accelData);

	sio::writeInt(getXYZ(0));
	sio::writeInt(getXYZ(1));
	sio::writeInt(getXYZ(2));

	sio::writeByte(sio::gyroSensor);
	sio::writeInt(sio::gyroData);

	sio::writeInt(getYPR(0));
	sio::writeInt(getYPR(1));
	sio::writeInt(getYPR(2));

	sio::writeByte(sio::dataFooter);
}