#ifndef ROBOT_LEKA_ARDUINO_MOTI_H_
#define ROBOT_LEKA_ARDUINO_MOTI_H_

/// \file Moti.h
/// \brief Moti, a new interactive spherical smart toy for children with Autism Spectrum Disorders
/// \author Ladislas de Toldi
/// \version 1.0

#include "Arduino.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


class MOTI {

/// \class MOTI
/// \brief MOTI class represents the robot
///
/// For simplicity purpose, we decided to build a class for the whole robot that would simplify the way we design and code the robot's behaviors and algorithms.
/// With MOTI class, you can access and manipulate everything you need, from motors to sensors and led.

	public:

		enum ColorName {
			DARK_RED,
			RED,
			PINK,
			PURPLE,
			BLUE,
			LIGHT_BLUE,
			WHITE,
			LIGHT_PINK,
			YELLOW,
			DARK_YELLOW,
			ORANGE,
			DARK_ORANGE,
			LIGHT_GREEN,
			GREEN
		};


		MOTI();


		void init();


		void initVerbose();




		//	SET CONSTANTS


		///
		/// \brief Constants initialization method
		///
		/// initializeConstants() is used to set all the constants to their default values.
		///
		void initializeConstants();

		///
		/// \brief Setter method for #_loopDelay
		/// \param value the value of #_loopDelay
		/// It is used to set the #_loopDelay.
		///
		void setLoopDelay(int value);
		///
		/// \brief Setter method for #_sleepDelay
		///
		/// It is used to set the #_sleepDelay.
		///
		void setSleepDelay(int value);
		///
		/// \brief Setter method for #_awakeThreshold
		///
		/// It is used to set theMOTI# _awakeThreshold.
		///
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
		void sendDataJson();
		void sendDataLearning();
		void sendDataBinaries();
		void sendBinaryByte(uint8_t value);
		void sendBinaryInt(int value);

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

		void colorSwitcher(ColorName color);

		void setRgbValue(int8_t index, int value);
		void setRed(int value);
		void setGreen(int value);
		void setBlue(int value);
		void setRgbValue(int redValue, int greenValue, int blueValue);

		uint8_t getRgbValue(uint8_t index);
		uint8_t getRed();
		uint8_t getGreen();
		uint8_t getBlue();

		void printRgbColor();
		void printRgbColor(ColorName colorName);
		void printRgbColor(int red, int green, int blue);

		void blinkLed(ColorName colorName, int numberOfBlinks, int timeBtwBlink);
		void blinkLed(int red, int green, int blue, int numberOfBlinks, int timeBtwBlink);

		void fadeLedTo(ColorName colorName);

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

		int getXYZ(uint8_t index);
		int getYPR(uint8_t index);

		void computeSensorValues();
		void updateLastSensorValues();


		//	GENERAL
		void setAllToLow();
		void softwareReset();


	private:

		//	VARIABLES
		int16_t rgb[3], rgbBuffer[3];
		uint16_t rightMotorSpeed, rightMotorSpeedBuffer;
		uint16_t leftMotorSpeed, leftMotorSpeedBuffer;
		int16_t XYZ[3], lastXYZ[3], deltaXYZ[3];
		float YPR[3], lastYPR[3], deltaYPR[3];
		uint16_t sleepy;

		uint16_t _loopDelay;
		uint16_t _sleepDelay;
		uint16_t _awakeThreshold;
		uint16_t _deltaAccelThreshold;
		uint16_t _highActivityThreshold;

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


		//	CONSTANTS
		static const uint8_t DEFAULT_LOOP_DELAY              = 75;
		static const uint16_t DEFAULT_SLEEP_DELAY             = 600;
		static const uint16_t DEFAULT_AWAKE_THRESHOLD         = 300;
		static const uint16_t DEFAULT_DELTA_ACCEL_THRESHOLD   = 200;
		static const uint8_t DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;

		static const uint8_t DEFAULT_LED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_RED_MAX_BRIGHTNESS   = 255;
		static const uint8_t DEFAULT_GREEN_MAX_BRIGHTNESS = 255;
		static const uint8_t DEFAULT_BLUE_MAX_BRIGHTNESS  = 255;

		static const uint8_t DEFAULT_MIN_MOTOR_SPEED = 0;
		static const uint8_t DEFAULT_MAX_MOTOR_SPEED = 255;

		static const uint8_t turnCoefficientTime = 80;
		static const uint8_t turnCoefficientDiv = 100;

		//	MOTOR PINS
		static const uint8_t leftMotorSpeedPin      = 5;
		static const uint8_t leftMotorDirectionPin  = 4;
		static const uint8_t rightMotorSpeedPin     = 6;
		static const uint8_t rightMotorDirectionPin = 7;

		//	LED PINS
		static const uint8_t RED_PIN   = 9;
		static const uint8_t GREEN_PIN = 10;
		static const uint8_t BLUE_PIN  = 11;

		//	DATA TRANSFERT
		static const uint8_t INIT_PHASE        = 0xAA;

		static const uint8_t START_ANSWER      = 0x0F;
		static const uint8_t END_ANSWER        = 0xF0;
		static const uint8_t NUMBER_OF_SENSORS = 0x02;

		static const uint8_t ACC_SENSOR        = 0x01;
		static const uint8_t ACC_DATA        = 0x06;
		static const uint8_t GYR_SENSOR        = 0x02;
		static const uint8_t GYR_DATA       = 0x06;

		RGBLED rgbled = RGBLED(9, 10,11);
		FreeSixIMU AccelGyro;

};

#endif