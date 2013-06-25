#ifndef ROBOT_LEKA_ARDUINO_MOTI_H_
#define ROBOT_LEKA_ARDUINO_MOTI_H_

#include "Arduino.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


class MOTI {

	public:

		//	CONSTRUCTORS
		MOTI();
		// static MOTI & getInstance();

		RGBLED rgbled = RGBLED(9, 10,11);
		FreeSixIMU AccelGyro = FreeSixIMU();

		void init();

		void initializeConstants();

		//	SET CONSTANTS
		void setLoopDelay(int value);
		void setSleepDelay(int value);
		void setAwakeThreshold(int value);
		void setDeltaAccelThreshold(int value);
		void setHighActivityThreshold(int value);

		void setLedMaxBrightness(int value);
		void setRedMaxBrightness(int value);
		void setGreenMaxBrightness(int value);
		void setBlueMaxBrightness(int value);

		void setMotorMinSpeed(int value);
		void setMotorMaxSpeed(int value);


		//	GET CONSTANTS
		int getLoopDelay();          	//	Delay used at the end of void loop() - The higher, the slower the robot is.
		int getSleepDelay();           	//	Time to elapse before the robot goes to sleep
		int getAwakeThreshold();       	//	DO NOT USE A VALUE HIGHER THAN 150 - This threshold is used to wake up the card. The higher, the harder it is to wake up.
		int getDeltaAccelThreshold();  	//	Threshold used to know if the accelerometer has moved between 2 cycles
		int getHighActivityThreshold();	//	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement.

		int getLedMaxBrightness();     	//	Maximum led brightness
		int getRedMaxBrightness();
		int getGreenMaxBrightness();
		int getBlueMaxBrightness();

		int getMotorMinSpeed();
		int getMotorMaxSpeed();


    	//	RESET CONSTANTS
		void resetLoopDelay();
		void resetSleepDelay();
		void resetAwakeThreshold();
		void resetDeltaAccelThreshold();
		void resetHighActivityThreshold();

		void resetLedMaxBrightness();
		void resetRedMaxBrightness();
		void resetGreenMaxBrightness();
		void resetBlueMaxBrightness();

		void resetMotorMinSpeed();
		void resetMotorMaxSpeed();


		//	DATA TRANSFER TO COMPUTER
		void sendDataToProcessing();
		void sendDataToDebug();
		void sendDataJson();

		//	STATE
		void initializeStates();

		bool isMoving();
		bool isSleeping();
		bool isWaiting();
		bool isAwake();
		bool isManipulated();
		bool isRemote();

		void setMovingState(bool state);
		void setSleepingState(bool state);
		void setWaitingState(bool state);
		void setAwakeState(bool state);
		void setManipulatedState(bool state);
		void setRemoteState(bool state);


		//	LED
		void initializeLed();

		void constrainRgbValue();

		void colorSwitcher( char * color);

		void setRgbValue(int value);
		void setRgbValue(int redValue, int greenValue, int blueValue);

		void printRgbColor();
		void printRgbColor(int red, int green, int blue);

		void blinkLed(int numberOfBlinks);
		void blinkLed(int numberOfBlinks, char * colorName);
		void fadeLedTo(char * colorName);

		void turnLedOff();
		void turnLedOn();


		//	MOTORS
		void initializeMotors();

		void spinRightWheel(uint8_t speed, bool direction);
		void spinLeftWheel(uint8_t speed, bool direction);

		void goForward();
		void goForward(int speed);

		void goBackward();
		void goBackward(int speed);

		void goLeft();
		void goLeft(int speed);
		void goRight();
		void goRight(int speed);

		void spinLeft();
		void spinLeft(int speed);
		void spinRight();
		void spinRight(int speed);

		void stop();


		//	SENSORS
		void checkSensors();
		void checkAccelerometer();
		void checkGyroscope();

		void computeSensorValues();
		void updateLastSensorValues();


		//	GENERAL
		void setAllToLow();
		void softwareReset();


	private:

		//	VARIABLES
		int rgb[3], rgbBuffer[3];
		int rightMotorSpeed, rightMotorSpeedBuffer;
		int leftMotorSpeed, leftMotorSpeedBuffer;
		int XYZ[3], lastXYZ[3], deltaXYZ[3];
		float YPR[3], lastYPR[3], deltaYPR[3];
		word sleepy;

		word _loopDelay;
		word _sleepDelay;
		word _awakeThreshold;
		word _deltaAccelThreshold;
		word _highActivityThreshold;

		uint8_t _ledMaxBrightness;
		uint8_t _redMaxBrightness;
		uint8_t _greenMaxBrightness;
		uint8_t _blueMaxBrightness;

		uint8_t _motorMinSpeed;
		uint8_t _motorMaxSpeed;

		bool _stateMoving;
		bool _stateSleeping;
		bool _stateWaiting;
		bool _stateAwake;
		bool _stateManipulated;
		bool _stateRemote;

};

	//	CONSTANTS
	const int DEFAULT_LOOP_DELAY              = 75;
	const int DEFAULT_SLEEP_DELAY             = 600;
	const int DEFAULT_AWAKE_THRESHOLD         = 300;
	const int DEFAULT_DELTA_ACCEL_THRESHOLD   = 200;
	const int DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;

	const uint8_t DEFAULT_LED_MAX_BRIGHTNESS   = 255;
	const uint8_t DEFAULT_RED_MAX_BRIGHTNESS   = 255;
	const uint8_t DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
	const uint8_t DEFAULT_BLUE_MAX_BRIGHTNESS  = 255;

	const uint8_t DEFAULT_MIN_MOTOR_SPEED = 0;
	const uint8_t DEFAULT_MAX_MOTOR_SPEED = 255;

	const uint8_t turnCoefficient = 8/10;

	//	MOTOR PINS
	const uint8_t leftMotorSpeedPin      = 5;
	const uint8_t leftMotorDirectionPin  = 4;
	const uint8_t rightMotorSpeedPin     = 6;
	const uint8_t rightMotorDirectionPin = 7;

	//	LED PINS
	const uint8_t RED_PIN   = 9;
	const uint8_t GREEN_PIN = 10;
	const uint8_t BLUE_PIN  = 11;

#endif