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

#include "Sensors.h"

/**
 * @file Sensors.cpp
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */

namespace Sensors {

	// Thread
	static WORKING_AREA(sensorsThreadArea, 230);
	bool _isInitialized = false;
	bool _isStarted = false;
	uint16_t _threadDelay = 50;

	// FreeIMU object
	FreeIMU _imu = FreeIMU();

	// FreeIMU variables
	uint8_t SENSORS_INACTIVITY_THRESHOLD = 75;
	uint8_t SENSORS_INACTIVITY_TIME = 10;
	uint8_t SENSORS_INACTIVITY_X = 1;
	uint8_t SENSORS_INACTIVITY_Y = 1;
	uint8_t SENSORS_INACTIVITY_Z = 1;

	// Variables
	float _XYZ[3] = { 0.f, 0.f, 0.f };
	float _YPR[3] = { 0.f, 0.f, 0.f };
	float _PTP[3] = { 0.f, 0.f, 0.f };

	float _returnXYZ = 0.f;
	float _returnYPR = 0.f;
	float _returnPTP = 0.f;

	// ChibiOS
	MUTEX_DECL(_SensorsDataMutex);

}

void Sensors::init(void* arg, tprio_t priority) {

	if (!_isInitialized) {
		_isInitialized = true;

		_imu.init();

		_imu.acc.setInactivityThreshold(SENSORS_INACTIVITY_THRESHOLD);
		_imu.acc.setTimeInactivity(SENSORS_INACTIVITY_TIME);
		_imu.acc.setInactivityX(SENSORS_INACTIVITY_X);
		_imu.acc.setInactivityY(SENSORS_INACTIVITY_Y);
		_imu.acc.setInactivityZ(SENSORS_INACTIVITY_Z);

		_imu.acc.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);
		_imu.acc.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);

		_imu.acc.setFreeFallThreshold(8);
		_imu.acc.setFreeFallDuration(3);

		_imu.acc.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN);
		_imu.acc.setInterrupt(ADXL345_INT_FREE_FALL_BIT, 1);

		(void)chThdCreateStatic(sensorsThreadArea, sizeof(sensorsThreadArea),
				priority, thread, arg);

	}

}

/**
 * @brief Starts the module
 */
void Sensors::start(void) {

	_isStarted = true;

}

/**
 * @brief Stops the module
 */
void Sensors::stop(void) {

	_isStarted = false;

}

/**
 * @brief Main module thread
 */
msg_t Sensors::thread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {

		if(_isStarted) {

			readXYZ();
			readYPR();

		}

		waitMs(_threadDelay);

	}

	return (msg_t)0;

}

void Sensors::readXYZ(void) {

	chMtxLock(&_SensorsDataMutex);
	_imu.getValues(_XYZ);
	chMtxUnlock();

}

void Sensors::readYPR(void) {

	chMtxLock(&_SensorsDataMutex);
	_imu.getYawPitchRollEulerRad(_YPR, _PTP);
	chMtxUnlock();

}

/**
 * @brief Reads the values XYZ of the accelerometer
 * @param x pointer that will receive the content of the X-axis
 * @param y pointer that will receive the content of the Y-axis
 * @param z pointer that will receive the content of the Z-axis
 */
void Sensors::getAccXYZ(float* x, float* y, float* z) {

	chMtxLock(&_SensorsDataMutex);
	*x = _XYZ[0];
	*y = _XYZ[1];
	*z = _XYZ[2];
	chMtxUnlock();

}

float Sensors::getAccXYZ(uint8_t index) {

	chMtxLock(&_SensorsDataMutex);
	_returnXYZ = _XYZ[index];
	chMtxUnlock();

	return _returnXYZ;

}

/**
 * @brief Getter method to get the X-axis value on the accelerometer
 * @return the X-axis accelerometer value
 */
float Sensors::getAccX() {

	chMtxLock(&_SensorsDataMutex);
	_returnXYZ = _XYZ[0];
	chMtxUnlock();

	return _returnXYZ;

}

/**
 * @brief Getter method to get the Y-axis value on the accelerometer
 * @return the Y-axis accelerometer value
 */
float Sensors::getAccY() {

	chMtxLock(&_SensorsDataMutex);
	_returnXYZ = _XYZ[1];
	chMtxUnlock();

	return _returnXYZ;

}

/**
 * @brief Getter method to get the Z-axis value on the accelerometer
 * @return the Z-axis accelerometer value
 */
float Sensors::getAccZ() {

	chMtxLock(&_SensorsDataMutex);
	_returnXYZ = _XYZ[2];
	chMtxUnlock();

	return _returnXYZ;

}

/**
 * @brief Reads the yaw, pitch and roll on the gyroscope (in radians)
 * @param y pointer that will receive the content of the yaw
 * @param p pointer that will receive the content of the pitch
 * @param r pointer that will receive the content of the roll
 */
void Sensors::getGyrYPR(float* y, float* p, float* r) {

	chMtxLock(&_SensorsDataMutex);
	*y = _YPR[0];
	*p = _YPR[1];
	*r = _YPR[2];
	chMtxUnlock();

}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrYPR(uint8_t index) {

	chMtxLock(&_SensorsDataMutex);
	_returnYPR = _YPR[index];
	chMtxUnlock();

	return _returnYPR;

}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrY() {

	chMtxLock(&_SensorsDataMutex);
	_returnYPR = _YPR[0];
	chMtxUnlock();

	return _returnYPR;

}

/**
 * @brief Reads the pitch on the gyroscope (in radians)
 * @return the pitch
 */
float Sensors::getGyrP() {

	chMtxLock(&_SensorsDataMutex);
	_returnYPR = _YPR[1];
	chMtxUnlock();

	return _returnYPR;

}

/**
 * @brief Reads the roll on the gyroscope (in radians)
 * @return the roll
 */
float Sensors::getGyrR() {

	chMtxLock(&_SensorsDataMutex);
	_returnYPR = _YPR[2];
	chMtxUnlock();

	return _returnYPR;

}

/**
 * @brief Reads the yaw, pitch and roll on the gyroscope (in degrees)
 * @param y pointer that will receive the content of the yaw
 * @param p pointer that will receive the content of the pitch
 * @param r pointer that will receive the content of the roll
 */
void Sensors::getGyrYPRDeg(float* y, float* p, float* r) {
	getGyrYPR(y, p, r);

	chMtxLock(&_SensorsDataMutex);
	*y = radToDeg(*y);
	*p = radToDeg(*p);
	*r = radToDeg(*r);
	chMtxUnlock();

}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrYPRDeg(uint8_t index) {

	return radToDeg(_YPR[index]);

}

/**
 * @brief Reads the yaw on the gyroscope (in degrees)
 * @return the yaw
 */
float Sensors::getGyrYDeg() {

	return radToDeg(getGyrY());

}

/**
 * @brief Reads the pitch on the gyroscope (in degrees)
 * @return the pitch
 */
float Sensors::getGyrPDeg() {

	return radToDeg(getGyrP());

}

/**
 * @brief Reads the roll on the gyroscope (in degrees)
 * @return the roll
 */
float Sensors::getGyrRDeg() {

	return radToDeg(getGyrR());

}

/**
 * @brief Reads the euler angles on the gyroscope (in radians)
 * @param phi pointer that will receive the content of the Phi angle
 * @param theta pointer that will receive the content of the Theta angle
 * @param psi pointer that will receive the content of the Psi angle
 */
void Sensors::getEuler(float* phi, float* theta, float* psi) {

	chMtxLock(&_SensorsDataMutex);
	*phi = _PTP[0];
	*theta = _PTP[1];
	*psi = _PTP[2];
	chMtxUnlock();

}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPTP(uint8_t index) {

	chMtxLock(&_SensorsDataMutex);
	_returnPTP = _PTP[index];
	chMtxUnlock();

	return _returnPTP;

}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPhi() {

	chMtxLock(&_SensorsDataMutex);
	_returnPTP = _PTP[0];
	chMtxUnlock();

	return _returnPTP;

}

/**
 * @brief Reads the Theta angle on the gyroscope (in radians)
 * @return Theta
 */
float Sensors::getEulerTheta() {

	chMtxLock(&_SensorsDataMutex);
	_returnPTP = _PTP[1];
	chMtxUnlock();

	return _returnPTP;

}

/**
 * @brief Reads the Psi angle on the gyroscope (in radians)
 * @return Psi
 */
float Sensors::getEulerPsi() {

	chMtxLock(&_SensorsDataMutex);
	_returnPTP = _PTP[2];
	chMtxUnlock();

	return _returnPTP;

}

/**
 * @brief Reads the euler angles on the gyroscope (in degrees)
 * @param phi pointer that will receive the content of the Phi angle
 * @param theta pointer that will receive the content of the Theta angle
 * @param psi pointer that will receive the content of the Psi angle
 */
void Sensors::getEulerDeg(float* phi, float* theta, float* psi) {

	getEuler(phi, theta, psi);

	chMtxLock(&_SensorsDataMutex);
	*phi = radToDeg(*phi);
	*theta = radToDeg(*theta);
	*psi = radToDeg(*psi);
	chMtxUnlock();

}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPTPDeg(uint8_t index) {

	return radToDeg(getEulerPTP(index));;

}

/**
 * @brief Reads the Phi angle on the gyroscope (in degrees)
 * @return Phi
 */
float Sensors::getEulerPhiDeg() {

	return radToDeg(getEulerPhi());

}

/**
 * @brief Reads the Theta angle on the gyroscope (in degrees)
 * @return Theta
 */
float Sensors::getEulerThetaDeg() {

	return radToDeg(getEulerTheta());

}

/**
 * @brief Reads the Psi angle on the gyroscope (in degrees)
 * @return Psi
 */
float Sensors::getEulerPsiDeg() {

	return radToDeg(getEulerPsi());

}

/**
 * @brief Checks whether the device is falling (see Configuration for threshold)
 * @return true if it is falling, flase otherwise
 */
bool Sensors::isFalling() {

	return _imu.acc.getInterruptSource(ADXL345_INT_FREE_FALL_BIT);

}

/**
 * @brief Checks whether the device is inactive (see Configuration for threshold)
 * @return true if it is inactive, flase otherwise
 */
bool Sensors::isInactive() {

	return _imu.acc.getInterruptSource(ADXL345_INT_INACTIVITY_BIT);

}

/**
 * @brief Converts a radians angle into degrees
 * @return the angle in degrees
 */
float Sensors::radToDeg(float rad) {

	return rad * 180.0f / M_PI;

}

/**
 * @brief Converts a radians angle into degrees
 * @return the angle in radians
 */
float Sensors::degToRad(float deg) {

	return deg * M_PI / 180.0f;

}

