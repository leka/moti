#ifndef LEKA_MOTI_ARDUINO_ROBOT_H_
#define LEKA_MOTI_ARDUINO_ROBOT_H_

/**
 * @file Moti.h
 * @brief Moti is a new interactive spherical smart toy for children with Autism Spectrum Disorders
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include <Arduino.h>
#include <Wire.h>
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Memory.h>


/**
 * @class Moti
 * @brief The Moti class represent the robot.
 *
 * For simplicity purpose, we decided to build a class for the whole robot that would simplify the way we design and code the robot's behaviors and algorithms.
 * With Moti class, you can access and manipulate everything you need, from motors to sensors and led.
 */
class Moti {

	public:

		Moti();


		void init(Sensors& sensors, Motors& motors);
		void initDebug(Sensors& sensors, Motors& motors);


		//	SET CONSTANTS
		void initializeConstants();

		void setLoopDelay(int value);

		void setSleepDelay(int value);

		void setAwakeThreshold(int value);
		void setDeltaAccelThreshold(int value);
		void setHighActivityThreshold(int value);


		//	GET CONSTANTS
		int getLoopDelay();
		int getSleepDelay();
		int getAwakeThreshold();
		int getDeltaAccelThreshold();
		int getHighActivityThreshold();


    	//	RESET CONSTANTS
		void resetLoopDelay();
		void resetSleepDelay();
		void resetAwakeThreshold();
		void resetDeltaAccelThreshold();
		void resetHighActivityThreshold();


		//	DATA TRANSFER TO COMPUTER
		void sendJson(Sensors& sensors);
		void sendBinaryData(Sensors& sensors);
		void writeBinaryByte(uint8_t value);
		void writeBinaryInt(int value);


		//	REMOTE CONTROL
		void readCommands(Motors& motors, Led& led, Sensors& sensors);
		void serialRouter();
		void serialServer();

		//	ACTIONS
		void stabilize(Sensors& sensors, Motors& motors);


		//	STATE
		void initializeStates();

		bool getMovingState();
		bool getSleepingState();
		bool getWaitingState();
		bool getAwakeState();
		bool getManipulatedState();
		bool getRemoteState();
		bool getLearningState();

		void setMovingState(bool state);
		void setSleepingState(bool state);
		void setWaitingState(bool state);
		void setAwakeState(bool state);
		void setManipulatedState(bool state);
		void setRemoteState(bool state);
		void setLearningState(bool state);


		//	GENERAL
		void softwareReset();

	private:

		//	VARIABLES
		uint16_t sleepy;

		uint16_t _loopDelay;
		uint16_t _sleepDelay;
		uint16_t _awakeThreshold;
		uint16_t _deltaAccelThreshold;
		uint16_t _highActivityThreshold;

		bool _stateMoving;
		bool _stateSleeping;
		bool _stateWaiting;
		bool _stateAwake;
		bool _stateManipulated;
		bool _stateRemote;
		bool _stateLearning;

		//	CONSTANTS
		static const uint8_t DEFAULT_LOOP_DELAY              = 75;
		static const uint8_t DEFAULT_HIGH_ACTIVITY_THRESHOLD = 80;
		static const uint16_t DEFAULT_SLEEP_DELAY            = 600;
		static const uint16_t DEFAULT_AWAKE_THRESHOLD        = 300;
		static const uint16_t DEFAULT_DELTA_ACCEL_THRESHOLD  = 200;

		//	DATA TRANSFERT I/O
		static const uint8_t DATA_HEADER = 0x0f;
		static const uint8_t DATA_FOOTER = 0xf0;
		static const uint8_t READY_TO_ANSWER = 0xff;

		static const uint8_t INIT_PHASE        = 0xAA;

		static const uint8_t START_ANSWER      = 0x0F;
		static const uint8_t END_ANSWER        = 0xF0;
		static const uint8_t NUMBER_OF_SENSORS = 0x02;

		static const uint8_t ACC_SENSOR        = 0x01;
		static const uint8_t ACC_DATA          = 0x06;
		static const uint8_t GYR_SENSOR        = 0x02;
		static const uint8_t GYR_DATA          = 0x06;

		// RELATED CLASSES
};

#endif