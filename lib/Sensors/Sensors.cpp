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
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


float Sensors::_XYZ[6] = { 0.f };
float Sensors::_YPR[3] = { 0.f };
float Sensors::_PTP[3] = { 0.f };
FreeIMU Sensors::_imu = FreeIMU();
uint32_t Sensors::_lastTimeXYZ = 0;
uint32_t Sensors::_lastTimeYPR = 0;
bool Sensors::_isInit = false;


void Sensors::getAccXYZ(float* x, float* y, float* z) {
	readXYZ();

	*x = _XYZ[0];
	*y = _XYZ[1];
	*z = _XYZ[2];
}

float Sensors::getAccX() {
	readXYZ();
	
	return _XYZ[0];
}

float Sensors::getAccY() {
	readXYZ();
	
	return _XYZ[1];
}

float Sensors::getAccZ() {
	readXYZ();
	
	return _XYZ[2];
}

void Sensors::getGyrYPR(float* y, float* p, float* r) {
	readYPR();

	*y = _YPR[0];
	*p = _YPR[1];
	*r = _YPR[2];
}

float Sensors::getGyrY() {
	readYPR();

	return _YPR[0];
}

float Sensors::getGyrP() {
	readYPR();

	return _YPR[1];
}

float Sensors::getGyrR() {
	readYPR();

	return _YPR[2];
}

void Sensors::getEuler(float* phi, float* theta, float* psi) {
	readYPR();

	*phi = _PTP[0];
	*theta = _PTP[1];
	*psi = _PTP[2];
}

float Sensors::getEulerPhi() {
	readYPR();

	return _PTP[0];
}

float Sensors::getEulerTheta() {
	readYPR();

	return _PTP[1];
}

float Sensors::getEulerPsi() {
	if (abs(millis() - _lastTimeYPR) > 50)
		readYPR();

	return _PTP[2];
}

void Sensors::getGyrYPRDeg(float* y, float* p, float* r) {
	getGyrYPR(y, p, r);

	*y = radToDeg(*y);
	*p = radToDeg(*p);
	*r = radToDeg(*r);
}

float Sensors::getGyrYDeg() {
	return radToDeg(getGyrY());
}

float Sensors::getGyrPDeg() {
	return radToDeg(getGyrP());
}

float Sensors::getGyrRDeg() {
	return radToDeg(getGyrR());
}

void Sensors::getEulerDeg(float* phi, float* theta, float* psi) {
	getEuler(phi, theta, psi);

	*phi = radToDeg(*phi);
	*theta = radToDeg(*theta);
	*psi = radToDeg(*psi);
}

float Sensors::getEulerPhiDeg() {
	return radToDeg(getEulerPhi());
}

float Sensors::getEulerThetaDeg() {
	return radToDeg(getEulerTheta());
}

float Sensors::getEulerPsiDeg() {
	return radToDeg(getEulerPsi());
}

bool Sensors::isFalling() {
	return _imu.acc.getInterruptSource(ADXL345_INT_FREE_FALL_BIT);
}

bool Sensors::isInactive() {
	return _imu.acc.getInterruptSource(ADXL345_INT_INACTIVITY_BIT);
}

float Sensors::radToDeg(float rad) {
	return rad * 180.0f / M_PI;
}

float Sensors::degToRad(float deg) {
	return deg * M_PI / 180.0f;
}


void Sensors::init(void) {
	if (!_isInit) {
		_isInit = true;

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

void Sensors::readXYZ(void) {
	if (!_isInit)
		init();

	if (abs(millis() - _lastTimeXYZ < SENSORS_REFRESH_DELAY))
		return;

	_imu.getValues(_XYZ);
	_lastTimeXYZ = millis();
}

void Sensors::readYPR(void) {
	if (!_isInit)
		init();

	if (abs(millis() - _lastTimeYPR < SENSORS_REFRESH_DELAY))
		return;

	_imu.getYawPitchRollEulerRad(_YPR, _PTP);
	_lastTimeYPR = millis();
}
