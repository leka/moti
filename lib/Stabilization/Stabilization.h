#ifndef LEKA_MOTI_BEHAVIOR_STABILIZATION_H_
#define LEKA_MOTI_BEHAVIOR_STABILIZATION_H_

#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Sensors.h"
#include "DriveSystem.h"
#include "Motion.h"

#include "Filters.h"

namespace Stabilization {

	// Thread methods
	static WORKING_AREA(stabilizationThreadArea, 256);
	static msg_t thread(void* arg);


	void init(void* arg = NULL, tprio_t priority = NORMALPRIO);
	void start(void);
	void stop(void);
	void wiggle(void);

	void orientateLeft(void);
	void orientateRight(void);

	PID _filterPsi;
	PID _filterTheta(100,0.0,5);
	PID _filterPhi;

	float _PIDOutputPsi = 0.0;
	float _PIDOutputTheta = 0.0;
	float _PIDOutputPhi = 0.0;

	// Variables
	bool _isInitialized = false;
	bool _isStarted = false;
	uint8_t _threadDelay = 100;
	uint32_t _runStartTime = 0;


	// Misc
	MUTEX_DECL(_stabMutex);
  
}

void Stabilization::init(void* arg, tprio_t priority) {
	if (!_isInitialized) {
		_isInitialized = true;

		(void)chThdCreateStatic(stabilizationThreadArea,
				sizeof(stabilizationThreadArea),
				priority, thread, arg);
	}
}

void Stabilization::start(void) {
	chMtxLock(&_stabMutex);

	_isStarted = true;
	_runStartTime = millis();

	chMtxUnlock();
}

void Stabilization::stop(void) {
	chMtxLock(&_stabMutex);

	_isStarted = false;

	chMtxUnlock();
}

void Stabilization::wiggle(void){

	//DriveSystem::go(FORWARD,130);
	DriveSystem::turn(FORWARD,150,0);
	waitMs(100);
	DriveSystem::turn(FORWARD,0,150);
	waitMs(100);
	DriveSystem::stop();
}

void Stabilization::orientateLeft(void){
_filterPsi.SetInitialAngle(_filterPsi.GetInitialAngle()+(PI/12));
}

void Stabilization::orientateRight(void){
_filterPsi.SetInitialAngle(_filterPsi.GetInitialAngle()-(PI/12));

}

msg_t Stabilization::thread(void* arg) {

	// PI/9 = 20°
	// PI/4 = 45°

	(void) arg;

	float currentAnglePsi = 0.0;
	float currentAngleTheta = 0.0;
	float currentAnglePhi = 0.0;


	float input = 0.0;
	int16_t output = 0.0;

	uint8_t speedPsi = 0;
	uint8_t speedTheta = 0;
	uint8_t speedPhi = 0;
	
	int16_t accY = 0;

	uint32_t currentTime = 0;

	while (!chThdShouldTerminate()) {
		if (_isStarted) {

			currentTime = abs(millis() - _runStartTime);


			if (currentTime > 2000) {
				currentAnglePsi = Sensors::getEulerPsi();
				currentAngleTheta = Sensors::getEulerTheta();
				currentAnglePhi = Sensors::getEulerPhi();

			}

			

			//Code for New Stab implementation

			_PIDOutputPsi = _filterPsi.CalculatePID(currentAnglePsi);
			_PIDOutputTheta = _filterTheta.CalculatePID(currentAngleTheta);
			//_PIDOutputPhi = _filterPhi.CalculatePID(currentAnglePhi);

			//Perform anti-reset windup?

			speedPsi = (uint8_t)min(230,abs(_PIDOutputPsi));
			speedTheta = (uint8_t)min(230,abs(_PIDOutputTheta));
			//speedPhi = (uint8_t)min(230,abs(_PIDOutputPhi));

			if((currentTime > 2000) && abs(currentAnglePsi) > PI/9)
			{
				//DriveSystem::spin(_PIDOutputPhi > 0 ? RIGHT : LEFT,speedPsi);
				if(_PIDOutputPsi > 0)
				{
					DriveSystem::spin(RIGHT,speedPsi);
				}
				else if(_PIDOutputPsi < 0)
				{
					DriveSystem::spin(LEFT,speedPsi);	
				}
			}

			else if((currentTime > 2000) && abs(currentAngleTheta) > PI/9){
				//DriveSystem::go(_PIDOutputTheta > 0 ? FORWARD : BACKWARD, speedTheta);
				if(_PIDOutputTheta > 0)
				{
					DriveSystem::go(FORWARD,speedTheta);
				}
				else if(_PIDOutputTheta < 0)
				{
					DriveSystem::go(BACKWARD,speedTheta);	
				}
			}

			//  else if ((currentTime > 2000) && abs(currentAnglePhi) > 0.40){
			// // DriveSystem::turn(_PIDOutputPhi > 0 ? FORWARD : BACKWARD,)
			//  	if(_PIDOutputPhi > 0){
			//  		DriveSystem::turn(FORWARD,150,0);
			//  	}
			//  	else if(_PIDOutputPhi < 0){
			//  		DriveSystem::turn(FORWARD,0,150);
			//  	}
				// DriveSystem::go(FORWARD,120);
			//}

			else if((currentTime > 2000) && abs(currentAnglePhi) > PI/4){
			
				wiggle();
				waitMs(50);

			}


			else {
				DriveSystem::stop();
			}

			//End of new implementation;
		}

		waitMs(_threadDelay);

	}

	return (msg_t)0;
}

#endif
