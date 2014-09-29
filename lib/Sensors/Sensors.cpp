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

	// FreeIMU object
	FreeIMU _imu = FreeIMU();

	// FreeIMU variables
	uint8_t SENSORS_INACTIVITY_THRESHOLD = 75;
	uint8_t SENSORS_INACTIVITY_TIME = 10;
	uint8_t SENSORS_INACTIVITY_X = 1;
	uint8_t SENSORS_INACTIVITY_Y = 1;
	uint8_t SENSORS_INACTIVITY_Z = 1;
	uint8_t SENSORS_REFRESH_DELAY = 50;

	// Variables
	float _XYZ[6] = { 0.f };
	float _YPR[3] = { 0.f };
	float _PTP[3] = { 0.f };
	uint32_t _lastTimeXYZ = 0;
	uint32_t _lastTimeYPR = 0;
	bool _isInitialized = false;

	// ChibiOS
	MUTEX_DECL(_SensorsDataMutex);

}

void Sensors::init(void) {
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
	}
}

/**
 * @brief Reads the values XYZ of the accelerometer
 * @param x pointer that will receive the content of the X-axis
 * @param y pointer that will receive the content of the Y-axis
 * @param z pointer that will receive the content of the Z-axis
 */
void Sensors::getAccXYZ(float* x, float* y, float* z) {
	readXYZ();

	*x = _XYZ[0];
	*y = _XYZ[1];
	*z = _XYZ[2];
}

float Sensors::getAccXYZ(uint8_t index) {
	readXYZ();

	return _XYZ[index];
}

/**
 * @brief Getter method to get the X-axis value on the accelerometer
 * @return the X-axis accelerometer value
 */
float Sensors::getAccX() {
	readXYZ();

	return _XYZ[0];
}

/**
 * @brief Getter method to get the Y-axis value on the accelerometer
 * @return the Y-axis accelerometer value
 */
float Sensors::getAccY() {
	readXYZ();

	return _XYZ[1];
}

/**
 * @brief Getter method to get the Z-axis value on the accelerometer
 * @return the Z-axis accelerometer value
 */
float Sensors::getAccZ() {
	readXYZ();

	return _XYZ[2];
}

/**
 * @brief Reads the yaw, pitch and roll on the gyroscope (in radians)
 * @param y pointer that will receive the content of the yaw
 * @param p pointer that will receive the content of the pitch
 * @param r pointer that will receive the content of the roll
 */
void Sensors::getGyrYPR(float* y, float* p, float* r) {
	readYPR();

	*y = _YPR[0];
	*p = _YPR[1];
	*r = _YPR[2];
}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrYPR(uint8_t index) {
	readYPR();

	return _YPR[index];
}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrY() {
	readYPR();

	return _YPR[0];
}

/**
 * @brief Reads the pitch on the gyroscope (in radians)
 * @return the pitch
 */
float Sensors::getGyrP() {
	readYPR();

	return _YPR[1];
}

/**
 * @brief Reads the roll on the gyroscope (in radians)
 * @return the roll
 */
float Sensors::getGyrR() {
	readYPR();

	return _YPR[2];
}

/**
 * @brief Reads the yaw, pitch and roll on the gyroscope (in degrees)
 * @param y pointer that will receive the content of the yaw
 * @param p pointer that will receive the content of the pitch
 * @param r pointer that will receive the content of the roll
 */
void Sensors::getGyrYPRDeg(float* y, float* p, float* r) {
	getGyrYPR(y, p, r);

	*y = radToDeg(*y);
	*p = radToDeg(*p);
	*r = radToDeg(*r);
}

/**
 * @brief Reads the yaw on the gyroscope (in radians)
 * @return the yaw
 */
float Sensors::getGyrYPRDeg(uint8_t index) {
	readYPR();

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
	readYPR();

	*phi = _PTP[0];
	*theta = _PTP[1];
	*psi = _PTP[2];
}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPTP(uint8_t index) {
	readYPR();

	return _PTP[index];
}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPhi() {
	readYPR();

	return _PTP[0];
}

/**
 * @brief Reads the Theta angle on the gyroscope (in radians)
 * @return Theta
 */
float Sensors::getEulerTheta() {
	readYPR();

	return _PTP[1];
}

/**
 * @brief Reads the Psi angle on the gyroscope (in radians)
 * @return Psi
 */
float Sensors::getEulerPsi() {
	return _PTP[2];
}

/**
 * @brief Reads the euler angles on the gyroscope (in degrees)
 * @param phi pointer that will receive the content of the Phi angle
 * @param theta pointer that will receive the content of the Theta angle
 * @param psi pointer that will receive the content of the Psi angle
 */
void Sensors::getEulerDeg(float* phi, float* theta, float* psi) {
	getEuler(phi, theta, psi);

	*phi = radToDeg(*phi);
	*theta = radToDeg(*theta);
	*psi = radToDeg(*psi);
}

/**
 * @brief Reads the Phi angle on the gyroscope (in radians)
 * @return Phi
 */
float Sensors::getEulerPTPDeg(uint8_t index) {
	readYPR();

	return radToDeg(_PTP[index]);
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

void Sensors::readXYZ(void) {
	if (abs(millis() - _lastTimeXYZ < SENSORS_REFRESH_DELAY))
		return;

	_imu.getValues(_XYZ);
	_lastTimeXYZ = millis();
}

void Sensors::readYPR(void) {
	if (abs(millis() - _lastTimeYPR < SENSORS_REFRESH_DELAY))
		return;

	_imu.getYawPitchRollEulerRad(_YPR, _PTP);
	_lastTimeYPR = millis();
}
