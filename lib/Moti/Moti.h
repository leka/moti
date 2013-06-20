#ifndef __ROBOT_LEKA_ARDUINO_MOTI_H_
#define __ROBOT_LEKA_ARDUINO_MOTI_H_

#include "Arduino.h"

#include "Constants.h"
#include "Colors.h"

#include "FreeSixIMU.h"
#include "RGBLED.h"

class Moti {

	public:

		static Moti & getInstance();

		RGBLED rgbled = RGBLED(9, 10,11);
		FreeSixIMU AccelGyro = FreeSixIMU();

		//	SET CONSTANTS
		void setGlobalDelay(int value);
		void setSleepDelay(int value);
		void setAwakeThreshold(int value);
		void setDeltaAccelThreshold(int value);
		void setHighActivityThreshold(int value);

		void setLedMaxBrightness(int value);
		void setRedMaxBrightness(int value);
		void setGreenMaxBrightness(int value);
		void setBlueMaxBrightness(int value);

		//	GET CONSTANTS
		int getGlobalDelay();          	//	Delay used at the end of void loop() - The higher, the slower the robot is.
		int getSleepDelay();           	//	Time to elapse before the robot goes to sleep
		int getAwakeThreshold();       	//	DO NOT USE A VALUE HIGHER THAN 150 - This threshold is used to wake up the card. The higher, the harder it is to wake up.
		int getDeltaAccelThreshold();  	//	Threshold used to know if the accelerometer has moved between 2 cycles
		int getHighActivityThreshold();	//	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement.

		int getLedMaxBrightness();     	//	Maximum led brightness
		int getRedMaxBrightness();
		int getGreenMaxBrightness();
		int getBlueMaxBrightness();

    	//	RESET CONSTANTS
		void resetGlobalDelay(int value);
		void resetSleepDelay(int value);
		void resetAwakeThreshold(int value);
		void resetDeltaAccelThreshold(int value);
		void resetHighActivityThreshold(int value);

		void resetLedMaxBrightness(int value);
		void resetRedMaxBrightness(int value);
		void resetGreenMaxBrightness(int value);
		void resetBlueMaxBrightness(int value);


		//	DATA TRANSFER TO COMPUTER
		void sendDataToProcessing();
		void sendDataToDebug();
		void sendDataJson();

		//	LED
		void setRgbValue();
		void setRgbValue(int value);
		void setRgbValue(int redValue, int greenValue, int blueValue);

		void printRgbColor();
		void printRgbColor(int red, int green, int blue);

		void blinkLed(int numberOfBlinks);
		void fadeLedTo( void (*color) );

		void turnLedOff();
		void turnLedOn();

		//	MOTORS
		void goForward();
		void goForward(int time);

		void goBackward();
		void goBackward(int time);

		void turnAround();
		void turnAround(int time);

		void goLeft();
		void goRight();

		void stop();

		//	SENSORS
		void checkSensors();
		void checkAccelerometer();
		void checkGyroscope();

		//	GENERAL
		void setAllToLow();
		void shutDown();
		void softwareReset();

		//	VARIABLES
		static int rgb[3], rgbBuffer[3];


	private:

		//	CONSTRUCTORS
		Moti();

		//	VARIABLES
		int i;
		uint8_t rightMotor, rightMotorBuffer;
		uint8_t leftMotor, leftMotorBuffer;
		float XYZ[3], lastXYZ[3], deltaXYZ[3];
		float YPR[3], lastYPR[3], deltaYPR[3];
		int sleepy;

		int _globalDelay;
		int _sleepDelay;
		int _awakeThreshold;
		int _deltaAccelThreshold;
		int _highActivityThreshold;

		uint8_t _ledMaxBrightness;
		uint8_t _redMaxBrightness;
		uint8_t _greenMaxBrightness;
		uint8_t _blueMaxBrightness;

		//	LED
		void initializeLed();

		// MOTORS
		void initializeMotors();

		//	DEBUG
		bool isRemoteCtrl;
		bool isShutDown;

};

#endif