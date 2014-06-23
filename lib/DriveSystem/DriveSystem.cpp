#include <Arduino.h>
#include "DriveSystem.h"

/**
 * @file DriveSystem.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */

/**
 * @brief DriveSystem Class Constructor
 *
 * @param directionPin for Moti in its most up-to-date configuration, the pins are as follow: Left Dir = 4 / Left Speed = 5 // Right Dir = 7 / Right Speed = 6
 * @param speedPin
 */
DriveSystem::DriveSystem() :
	rMotor(Motor(DEFAULT_RIGHT_MOTOR_DIRECTION_PIN, DEFAULT_RIGHT_MOTOR_SPEED_PIN)),
	lMotor(Motor(DEFAULT_LEFT_MOTOR_DIRECTION_PIN, DEFAULT_LEFT_MOTOR_SPEED_PIN))
{

}

/*
 * @brief DriveSystem go Method
 *
 * @param direction should take 0 for backward, 1 for forward
 * @param speed the speed the motors should have
 */
void DriveSystem::go(Direction _direction, uint8_t _speed, uint32_t _time, uint16_t _launchTime) {
	launch(_direction, _speed, _launchTime);

	if (_time - _launchTime)
		chThdSleepMilliseconds(_time - _launchTime);
}

/*
 * @brief DriveSystem launch Method
 *
 * @param direction should take 0 for backward, 1 for forward
 * @param speed the speed the motors should have
 */
void DriveSystem::launch(Direction _direction, uint8_t _speed, uint16_t _launchTime) {
	uint32_t delayValue = 10;
	uint32_t nLoops = _launchTime / delayValue;

	uint8_t lInitSpeed = lSpeed;
	uint8_t rInitSpeed = rSpeed;

	if (lInitSpeed != rInitSpeed)
		Serial.print("Outch!");

	if (lInitSpeed == _speed)
		return;

	if (lDirection != _direction) {
		float leftSpd = (float)lSpeed;
		float part = leftSpd / ((float)_speed + leftSpd);

		stop((uint32_t)(_launchTime * part));

		lDirection = _direction;
		rDirection = _direction;

		launch(_direction, _speed, (uint32_t)(_launchTime * (1.f - part)));
	}

	for (uint32_t i = 0; i < nLoops; ++i) {
		lSpeed = lInitSpeed + (i * (_speed - lInitSpeed)) / nLoops;
		rSpeed = rInitSpeed + (i * (_speed - rInitSpeed)) / nLoops;

		activate();

		chThdSleepMilliseconds(delayValue);
	}

	lSpeed = _speed;
	rSpeed = _speed;

	activate();
}

/*
 * @brief DriveSystem spin Method
 *
 * @param direction should take 0 for backward, 1 for forward
 * @param speed the speed the motors should have
 */
void DriveSystem::spin(Sensors &sensors, Rotation spinDirection, uint8_t speed, uint16_t angle) {
	float alpha = sensors.getEuler(0);
	float currentAngle = alpha;
	float lastAngle = alpha;

	lSpeed = speed;
	rSpeed = speed;

	if (spinDirection == RIGHT) {
		lDirection = FORTH;
		rDirection = BACK;
	}
	else {
		rDirection = FORTH;
		lDirection = BACK;
	}

	activate();

	while (1) {
		float beta = angle >= 360 ? 90. : (float)angle;
		angle -= (uint16_t)beta;

		if (spinDirection == LEFT)
			beta = -beta;

		float destination = currentAngle + beta;

		if (abs(destination) >= 180.) {
			while (currentAngle * lastAngle >= 0) {
				lastAngle = currentAngle;
				currentAngle = sensors.getEuler(0);
			}

			destination = (360. + destination) * (spinDirection == LEFT ? 1. : -1.);
		}

		if (spinDirection == RIGHT) {
			while (destination > currentAngle)
				currentAngle = sensors.getEuler(0);
		}
		else {
			while (destination < currentAngle)
				currentAngle = sensors.getEuler(0);
		}

		if (angle == 0)
			break;
	}

	stop(0);
}

/*
 * @brief DriveSystem stop Method
 */
void DriveSystem::stop(uint32_t stopTime) {
	uint32_t delayValue = 10;
	uint32_t nLoops = stopTime / delayValue;

	uint8_t lInitSpeed = lSpeed;
	uint8_t rInitSpeed = rSpeed;

	if ((lInitSpeed == 0) && (rInitSpeed == 0))
		return;

	for (uint32_t i = 0; i < nLoops; ++i) {
		lSpeed = lInitSpeed - (i * lInitSpeed) / nLoops;
		rSpeed = rInitSpeed - (i * rInitSpeed) / nLoops;

		activate();

		chThdSleepMilliseconds(delayValue);
	}

	lDirection = FORTH;
	rDirection = FORTH;

	lSpeed = 0;
	rSpeed = 0;

	lMotor.stop();
	rMotor.stop();
}

/*
 * @brief DriveSystem turn function
 */
void DriveSystem::turn(Rotation turnDirection, uint8_t speed) {
	if (turnDirection == RIGHT) {
		rSpeed = speed;
		rDirection = FORTH;

		lSpeed = speed >= 30 ? (speed - 30) : 0;
		lDirection = BACK;
	}
	else {
		lSpeed = speed;
		lDirection = BACK;

		rSpeed = speed >= 30 ? (speed - 30) : 0;
		rDirection = FORTH;
	}

	activate();
}

void DriveSystem::activate() {
	lMotor.spin((bool)lDirection, lSpeed);
	rMotor.spin((bool)rDirection, rSpeed);
}

/*
 * @brief DriveSystem turn function
 */
// void DriveSystem::turn(int16_t angle, bool direction, uint8_t speed) const {
// 	// nothing to do here until we check is usefulness of this method...
// }
