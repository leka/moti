#include "Moti.h"
#include "Arduino.h"

/**
 * @brief Constant initialization method
 *
 * initializeConstants() is used to set all the constants to their default values.
 * It calls for resetLoopDelay(), resetSleepDelay(), resetAwakeThreshold(), resetDeltaAccelThreshold(), resetHighActivityThreshold(), resetLedMaxBrightness(), resetRedMaxBrightness(), resetGreenMaxBrightness(), resetBlueMaxBrightness(), resetMotorMinSpeed(), resetMotorMaxSpeed().
 */
void MOTI::initializeConstants(){
	resetLoopDelay();
	resetSleepDelay();
	resetAwakeThreshold();
	resetDeltaAccelThreshold();
	resetHighActivityThreshold();

	resetLedMaxBrightness();
	resetRedMaxBrightness();
	resetGreenMaxBrightness();
	resetBlueMaxBrightness();

	resetMotorMinSpeed();
	resetMotorMaxSpeed();
}

//###############//
// SET CONSTANTS //
//###############//

/**
 * @brief Setter method for _loopDelay
 *
 * Once set, the _loopDelay can be accessed by calling getLoopDelay()
 * @param value the value you want to assign to _loopDelay.
 */
void MOTI::setLoopDelay(int value){
	_loopDelay = value;
}

/**
 * @brief Setter method for _sleepDelay
 *
 * Once set, the _sleepDelay can be accessed by calling getSleepDelay()
 * @param value the value you want to assign to _sleepDelay.
 */
void MOTI::setSleepDelay(int value){
	_sleepDelay = value;
}

/**
 * @brief Setter method for _awakeThreshold
 *
 * Once set, the _sleepDelay can be accessed by calling getAwakeThreshold()
 * @param value the value you want to assign to _awakeThreshold.
 */
void MOTI::setAwakeThreshold(int value){
	_awakeThreshold = value;
}

/**
 * @brief Setter method for _deltaAccelThreshold
 *
 * Once set, the _sleepDelay can be accessed by calling getDeltaAccelThreshold()
 * @param value the value you want to assign to _delatAccelThreshold.
 */
void MOTI::setDeltaAccelThreshold(int value){
	_deltaAccelThreshold = value;
}

/**
 * @brief Setter method for _highAccelThreshold
 *
 * Once set, the _sleepDelay can be accessed by calling getHighAccelThreshold()
 * @param value the value you want to assign to _highAccelThreshold.
 */
void MOTI::setHighActivityThreshold(int value){
	_highActivityThreshold = value;
}



/**
 * @brief Setter method for _motorMinSpeed
 *
 * Once set, the _sleepDelay can be accessed by calling getMotorMinSpeed()
 * @param value the value you want to assign to _motorMinSpeed.
 */
void MOTI::setMotorMinSpeed(int value){
	_motorMinSpeed = value;
}

/**
 * @brief Setter method for _motorMaxSpeed
 *
 * Once set, the _sleepDelay can be accessed by calling getMotorMaxSpeed()
 * @param value the value you want to assign to _motorMaxSpeed.
 */
void MOTI::setMotorMaxSpeed(int value){
	_motorMaxSpeed = value;
}


//###############//
// GET CONSTANTS //
//###############//

/**
 * @brief Getter method for _loopDelay
 *
 * It is used to modify the speed of the loop: higher value means slower robot.
 * @return the value of _loopDelay
 */
int MOTI::getLoopDelay(){
	return _loopDelay;
}

/**
 * @brief Getter method for _sleepDelay
 *
 * It is used to as a counter to determine the moment the robot should got to sleep. Higher value means longer awaken state.
 * @return the value of _sleepDelay
 */
int MOTI::getSleepDelay(){
	return _sleepDelay;
}

/**
 * @brief Getter method for _awakeThreshold
 *
 * It is used to set the accelerometer variation above which the robot should wake up if touched.
 * @return the value of _awakeThreshold
 */
int MOTI::getAwakeThreshold(){
	return _awakeThreshold;
}

/**
 * @brief Getter method for _deltaAccelThreshold
 *
 * It is used as a comparison to check whether or not the robot has been touched. Higher value means a need for stronger interaction
 * @return the value of _deltaAccelThreshold
 */
int MOTI::getDeltaAccelThreshold(){
	return _deltaAccelThreshold;
}

/**
 * @brief Getter method for _highActivityThreshold
 *
 * It is used as a comparison to check whether or not the robot has been violently touched. Higher value means a need for ultraviolent interactions!
 * @return the value of _highActivityThreshold
 */
int MOTI::getHighActivityThreshold(){
	return _highActivityThreshold;
}



/**
 * @brief Getter method for _motorMinSpeed
 *
 * It is used to get the minimum speed needed to get the wheels spinning.
 * @return the value of _motorMinSpeed
 */
int MOTI::getMotorMinSpeed(){
	return _motorMinSpeed;
}

/**
 * @brief Getter method for _motorMaxSpeed
 *
 * It is used to get the maximum speed at which the wheels should be spinning.
 * @return the value of _motorMaxSpeed
 */
int MOTI::getMotorMaxSpeed(){
	return _motorMaxSpeed;
}


//#################//
// RESET CONSTANTS //
//#################//

/**
 * @brief Reset method for _loopDelay to initial value
 */
void MOTI::resetLoopDelay(){
	_loopDelay = DEFAULT_LOOP_DELAY;
}

/**
 * @brief Reset method for _sleepDelay to initial value
 */
void MOTI::resetSleepDelay(){
	_sleepDelay = DEFAULT_SLEEP_DELAY;
}

/**
 * @brief Reset method for _awakeThreshold to initial value
 */
void MOTI::resetAwakeThreshold(){
	_awakeThreshold = DEFAULT_AWAKE_THRESHOLD;
}

/**
 * @brief Reset method for _deltaAccelThreshold to initial value
 */
void MOTI::resetDeltaAccelThreshold(){
	_deltaAccelThreshold = DEFAULT_DELTA_ACCEL_THRESHOLD;
}

/**
 * @brief Reset method for _highActivityThreshold to initial value
 */
void MOTI::resetHighActivityThreshold(){
	_highActivityThreshold = DEFAULT_HIGH_ACTIVITY_THRESHOLD;
}



/**
 * @brief Reset method for _motorMinSpeed to initial value
 */
void MOTI::resetMotorMinSpeed(){
	_motorMinSpeed = DEFAULT_MIN_MOTOR_SPEED;
}

/**
 * @brief Reset method for _motorMaxSpeed to initial value
 */
void MOTI::resetMotorMaxSpeed(){
	_motorMaxSpeed = DEFAULT_MAX_MOTOR_SPEED;
}

