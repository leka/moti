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
void Moti::init(Sensors& sensors, Motors& motors){
	delay(500);
	serial.begin(115200);
	delay(50);
	motors.init();
	delay(50);
	sensors.init();
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
void Moti::initDebug(Sensors& sensors, Motors& motors){
	delay(500);
	serial.begin(115200);
	delay(50);
	serial.println("SC");
	delay(50);
	motors.init();
	serial.println("MOTORS");
	delay(50);
	sensors.init();
	serial.println("IMU");
	delay(50);
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

/**
 * @class stabilze
 * @brief The stabilze class represents the stabilization of the robot in the start position.
 *
 * This class corrects the variation of the initial position of the robot inside the ball to be everytime in the same position relative.
 */
void Moti::stabilize(Sensors& sensors, Motors& motors){


	sensors.checkGyroscope();  //@ Check the Gyroscope initial values.


	while (abs(sensors.getYPR(0)) > 3) { 	//@ How these values are initializes at zero, they are compared with -3 and 3 and do the position upgrade with this tolerance.


		sensors.checkGyroscope();	

		if(sensors.getYPR(0) < 0){		motors.spinRight();	}   //@ If the value is negatif, the derivate is positive and go back to zero.

		else {		motors.spinLeft();		}	 //@ If the value is positive, the derivate is negative and go back to zero.


	} 


	while (abs(sensors.getYPR(2)) > 10) { 	//@ How these values are initializes at zero, they are compared with -10 and 10 and do the position upgrade with this tolerance.


		sensors.checkGyroscope();	

		if(sensors.getYPR(2) > 0){ motors.spinRight(); } //@ If the value is negatif, the derivate is positive and go back to zero and the inclination...
													//@ at YPR(2) is changed for one inclination at YPR(1) due to the ball geometry.
		else { motors.spinLeft(); }


	} 


	while (abs(sensors.getYPR(1)) > 3) { 	//@ YPR(1) finally correct the error in YPR(2) after the rotation and work independent.
 

		sensors.checkGyroscope();	

		if(sensors.getYPR(1) < 0){ motors.goForward(); } //@ If the value is negatif, goForward allows to go back to zero.

		else { motors.goBackward(); }	//@ If the value is positive, goBackward allows to go back to zero.


	} 


	motors.stop(); //

}

