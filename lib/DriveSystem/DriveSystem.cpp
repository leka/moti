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
 * @brief DriveSystem Spin Method
 *
 * @param direction should take 0 for backward, 1 for frontward
 * @param speed the speed the motors should have
 */
void DriveSystem::spin(bool direction, uint8_t speed) const {

}

/*
 * @brief DriveSystem stop Method
 */
void Motor::stop() const{

}

