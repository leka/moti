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
DriveSystem::DriveSystem(){
	// nothing to do here
}

/*
 * @brief DriveSystem go Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motors should have
 */
void DriveSystem::go(bool direction, uint8_t speed) const {
	rightMotor.spin(direction, speed);
	leftMotor.spin(direction, speed);
}

/*
 * @brief DriveSystem spin Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motors should have
 */
void DriveSystem::spin(bool spinDirection, uint8_t speed) const {
	if(spinDirection == RIGHT) {
		rightMotor.spin(0, speed);
		leftMotor.spin(1, speed);
	}
	else if(spinDirection == LEFT) {
		rightMotor.spin(1, speed);
		leftMotor.spin(0, speed);
	}
}

/*
 * @brief DriveSystem stop Method
 */
void DriveSystem::stop() const{
	rightMotor.stop();
	leftMotor.stop();
}

/*
 * @brief DriveSystem turn function
 */
void DriveSystem::turn(int16_t angle, bool direction, uint8_t speed) const {
	// nothing to do here until we check is usefulness of this method...
}