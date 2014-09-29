/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com>
   and Leka <http://weareleka.com>

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

#include "Moti.h"

/**
 * @file Moti.cpp
 * @author Ladislas de Toldi and Flavien Raynaud
 * @version 1.0
 */

namespace Moti {

	// VARIABLES

	// Thread states
	static WORKING_AREA(motiModuleThreadArea, 256);
	bool _isInitialized = false;
	bool _isStarted     = false;
	uint8_t _threadDelay = 100;

	// Moti states
	bool _isStuck           = false;
	uint8_t _stuckThreshold = 90;
	uint16_t _stuckTime     = 500;

	bool _isFalling      = false;

	bool _isShaken       = false;
	bool _isShakenXYZ[3] = {false, false, false};
	uint16_t _shakeTime  = 500;

	bool _isSpinning     = false;
	bool _isSpinningY    = false;
	bool _isSpinningP    = false;
	bool _isSpinningR    = false;

	// Stuck variables
	uint32_t _startStuckTime = 0;

	// Spin variables
	int16_t _nLaps   = 0;
	float _spinAngle = 0.f;
	float _spinHistory[HISTORY_SIZE] = {0.f};

	// Shake variables
	int16_t _lastXYZ[3]          = {0, 0, 0};
	int16_t _currentXYZ[3]       = {0, 0, 0};
	int16_t _deltaXYZ[3]         = {0, 0, 0};
	double _sqrtXYZ[3]           = {0, 0, 0};
	double _avrgXYZ[3]           = {0, 0, 0};
	double _alphaXYZ[3]          = {0.1, 0.1, 0.1};
	double _shakeThresholdXYZ[3] = {120, 120, 120};
	uint32_t _startShakeTime     = 0;
}

/**
 * @brief Start Moti's chThread
 */
void Moti::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;

		(void)chThdCreateStatic(motiModuleThreadArea,
				sizeof(motiModuleThreadArea),
				priority, moduleThread, arg);
	}
}

/**
 * @brief Tells the Moti thread to run and check for events
 */
void Moti::start(void) {
	_isStarted = true;
}

/**
 * @brief Tells the Moti thread to stop checking for event
 */
void Moti::stop(void) {
	_isStarted = false;
	_isStuck = false;
}

/**
 * @brief Check if Moti is stuck
 * @return true if stuck
 */
bool Moti::isStuck() {
	if (!_isInitialized)
		start();

	return _isStuck && (abs(millis() - _startStuckTime) > _stuckTime);
}

/**
 * @brief Check if Moti is shaken
 * @return true if shaken
 */
bool Moti::isShaken(void) {
	return _isShaken && (abs(millis() - _startShakeTime) > _shakeTime);
}

/**
 * @brief Check if Moti is shaken
 * @return true if shaken
 */
bool Moti::isShakenX(void) {
	return _isShakenXYZ[0] && (abs(millis() - _startShakeTime) > _shakeTime);
}

/**
 * @brief Check if Moti is shaken
 * @return true if shaken
 */
bool Moti::isShakenY(void) {
	return _isShakenXYZ[1] && (abs(millis() - _startShakeTime) > _shakeTime);
}

/**
 * @brief Check if Moti is shaken
 * @return true if shaken
 */
bool Moti::isShakenZ(void) {
	return _isShakenXYZ[2] && (abs(millis() - _startShakeTime) > _shakeTime);
}

/**
 * @brief Check if Moti is spun
 * @return true if spun
 */
bool Moti::isSpinning(void) {
	return _isSpinning;
}

/**
 * @brief Check if Moti is spun
 * @return true if spun
 */
bool Moti::isFalling(void) {
	return _isFalling;
}

/**
 * @brief Count the number of laps around the Z axis
 * @return number of laps
 */
uint8_t Moti::getLapsZ(void) {
	return (uint8_t)abs(_nLaps);
}

void Moti::detectStuck(void) {
	if (abs(Sensors::getAccX()) > _stuckThreshold) {
		if (!_isStuck) {
			_isStuck = true;
			_startStuckTime = millis();
		}
	}
	else {
		_isStuck = false;
	}
}

void Moti::detectSpin(void) {
	uint8_t i = 0;

	float currentAngle = 0.f;
	float oldAngle = 0.f;

	oldAngle = currentAngle;
	currentAngle = Sensors::getEulerPhiDeg();

	_spinHistory[i] = currentAngle;
	i = (i + 1) % HISTORY_SIZE;

	if (abs(Toolbox::arrayDeltaSum(_spinHistory, HISTORY_SIZE)) > 15.f) {
		_isSpinning = true;
	}
	else {
		_isSpinning = false;
		_nLaps = 0;
	}

	if (_isSpinning) {
		if ((currentAngle * oldAngle < 0.f) && (currentAngle * oldAngle > -8000.f)) {
			if (currentAngle > 0.f)
				_nLaps++;
			else
				_nLaps--;
		}
	}
}

void Moti::detectShake(void) {
	uint8_t i = 0;

	for (i = 0; i < 3; i++) {
		_currentXYZ[i] = (int)Sensors::getAccXYZ(i);
		_deltaXYZ[i]   = _lastXYZ[i] - _currentXYZ[i];
		_lastXYZ[i]    = _currentXYZ[i];
		_sqrtXYZ[i]    = sqrt(sq((double)_deltaXYZ[i]));
		_avrgXYZ[i]    = (_alphaXYZ[i] * _sqrtXYZ[i]) + (1.0 - _alphaXYZ[i]) * _avrgXYZ[i];


		if (_avrgXYZ[i] > _shakeThresholdXYZ[i]) {
			_isShakenXYZ[i] = true;
		}
		else {
			_isShakenXYZ[i] = false;
		}
	}

	if (_isShakenXYZ[0] || _isShakenXYZ[1] || _isShakenXYZ[2]) {
		if (!_isShaken) {
			_isShaken = true;
			_startShakeTime = millis();
		}
	}
	else {
		_isShaken = false;
	}
}

void Moti::detectFall(void) {

	_isFalling = Sensors::isFalling();

}

/**
 * @brief Main module thread
 */
msg_t Moti::moduleThread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {

		if (_isStarted) {

			Moti::detectStuck();
			Moti::detectSpin();
			Moti::detectShake();
			Moti::detectFall();

		}

		waitMs(_threadDelay);
	}

	return (msg_t)0;
}

