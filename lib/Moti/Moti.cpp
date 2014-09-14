#include "Moti.h"



namespace Moti {

	// VARIABLES

	// Thread states
	static WORKING_AREA(motiModuleThreadArea, 256);
	bool _isStarted = false;
	bool _isRunning = false;

	// Moti states
	bool _isStuck = false;

	bool _isShaken = false;
	bool _isShakenX = false;
	bool _isShakenY = false;
	bool _isShakenZ = false;

	bool _isSpinning = false;
	bool _isSpinningY = false;
	bool _isSpinningP = false;
	bool _isSpinningR = false;

	// Stuck variables
	uint32_t _startStuckTime = 0;

	// Spin variables
	int16_t _nLaps = 0;
	float _spinAngle = 0.f;
	float spinHistory[HISTORY_SIZE] = {0.f};

	// Shake variables
	int16_t lastXYZ[3] = {0};
	int16_t currentXYZ[3] = {0};
	int16_t deltaXYZ[3] = {0};

	double sqrtXYZ[3] = {0};
	double avrgXYZ[3] = {0};

	double alphaXYZ[3] = {0.1};

}


/**
 * @brief Tells the Moti thread to run and check for events
 */
void Moti::start(void) {
	_isRunning = true;
}

/**
 * @brief Tells the Moti thread to stop checking for event
 */
void Moti::stop(void) {
	_isRunning = false;
	_isStuck = false;
}

/**
 * @brief Check if Moti is stuck
 * @return true if stuck
 */
bool Moti::isStuck() {
	if (!_isStarted)
		start();

	return _isStuck && (abs(millis() - _startStuckTime) > ENVIRONMENT_STUCK_TIME);
}

/**
 * @brief Check if Moti is shaken
 * @return true if shaken
 */
bool Moti::isShaken(void) {
	return _isShaken;
}

/**
 * @brief Check if Moti is spun
 * @return true if spun
 */
bool Moti::isSpinning(void) {
	return _isSpinning;
}

/**
 * @brief Count the number of laps around the Z axis
 * @return number of laps
 */
uint8_t Moti::getLapsZ(void) {
	return (uint8_t)abs(_nLaps);
}

/**
 * @brief Start Moti's chThread
 */
void Moti::startThread(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;

		(void)chThdCreateStatic(motiModuleThreadArea,
								sizeof(motiModuleThreadArea),
								priority, moduleThread, arg);
	}
}

void Moti::detectStuck(void) {
	if (abs(Sensors::getAccX()) > ENVIRONMENT_STUCK_THRESHOLD) {
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

	spinHistory[i] = currentAngle;
	i = (i + 1) % HISTORY_SIZE;

	if (abs(Toolbox::arrayDeltaSum(spinHistory, HISTORY_SIZE)) > 15.f) {
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

}

void Moti::detectFall(void) {

}

msg_t Moti::moduleThread(void* arg) {

	(void) arg;

	while (!chThdShouldTerminate()) {
		if (_isRunning) {

			Moti::detectStuck();
			Moti::detectSpin();
			Moti::detectShake();
			Moti::detectFall();

		}

		waitMs(ENVIRONMENT_THREAD_DELAY);
	}

	return (msg_t)0;
}

