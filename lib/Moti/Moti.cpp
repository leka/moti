#include <Arduino.h>
#include <Moti.h>


//##############//
// CONSTRUCTORS //
//##############//

/**
 * @brief Moti Class Constructor
 */
Moti::Moti(){}

/**
 * @brief Initialization method
 *
 * init() initialized everything at the beginning of the program. It must be called inside void setup().
 * The list of all the methods it calls is as follow: Serial.begin(), initializeConstants(), initializeLed(), initializeStates(), Wire.begin(), AccelGyro.init(), initiliazeMotors().
 */
void Moti::init(){
	delay(500);
	Serial.begin(115200);
	delay(50);
}

/**
 * @brief Initialization method with verbose output
 *
 * initVerbose() does the same as init() but adds text output for debugging purpose. It should be used ONLY for development and NOT for production.
 * The list of all the methods it calls is as follow: Serial.begin(), initializeConstants(), Wire.begin(), AccelGyro.init(), initializeLed(), initializeStates(), initiliazeMotors().
 * If everything works fine it should output a list with "SC" --> "CST" --> "WIRE" --> "IMU" --> "LED" --> "STATES" --> "MOTORS".
 * If the list is not complete, it means that the initialization of the n+1 failed.
 *
 * For example, if the serial outputs "SC" --> "CST" --> "WIRE", it means that IMU is failing and needs a fix.
 */
void Moti::initDebug(){
	delay(500);
	Serial.begin(115200);
	delay(50);
	Serial.println("SC");
	delay(50);

	delay(50);
	Serial.println("IMU");
}


//#########//
// GENERAL //
//#########//

/**
 * @brief Reseting software
 *
 * softwareReset() resets the program so that it can restart before the void setup().
 * It may be used if you don't know how much time has passed since the last awaken state.
 * The environment may have change, so going through the void setup() again is required to re- init() everything.
 */
void Moti::softwareReset() {
	asm volatile ("  jmp 0");
}

