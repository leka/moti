/*
PID logic:
-Compute Error
-Apply PID algorithme (Gain, Integral &/or Derivative)
-PID output
-Live Output

*/

#include "Filters.h"


PID::~PID()
{
	_ErrorTracker.~RunningAverage();
}

PID::PID():_ErrorTracker(3)
{
	 _CycleTime = 1;
	 _Error=0.0;
	 _ErrorVariation=0.0;

	 _current_angle = 0.0;
	 _InitialAngle = 0.f;


	//Init values of filter
	 _PIDOutput = 0.0;
	 _Proportional = 0.0;
	 _Derivative = 0.0;
	 _Integral = 0.0;

	//PID coefficients
	 _Kp = 60;
	 _Ki = 0.0;
	 _Kd = 3;

	//_ErrorTracker(3);
	//_ErrorTracker = new RunningAverage(3);
	//Cyclic array for the filters
	_ErrorTracker.fillValue(0.0,3);
}

PID::PID(const float Kp, const float Ki, const float Kd):_ErrorTracker(3)
{
	 _CycleTime = 1;
	 _Error=0.0;
	 _ErrorVariation=0.0;

	 _current_angle = 0.0;
	 _InitialAngle = 0.f;


	//Initial values of filter
	 _PIDOutput = 0.0;
	 _Proportional = 0.0;
	 _Derivative = 0.0;
	 _Integral = 0.0;

	//PID coefficients
	 _Kp = Kp;
	 _Ki = Ki;
	 _Kd = Kd;

	//_ErrorTracker(3);
	//_ErrorTracker = new RunningAverage(3);
	//Cyclic array for the filters
	_ErrorTracker.fillValue(0.0,3);
}

void PID::SetInitialAngle(const float initialAngle){
	_InitialAngle = initialAngle;
}

float PID::GetInitialAngle(){
	return _InitialAngle;
}

float PID::CalculatePID(const float currentAngle)
{
	

	//Receive cycle time of the system
	//TBD

	//Calculate error

	//currentAngle = Sensors::getEulerPsi();
			_Error = _InitialAngle - currentAngle;
			_ErrorVariation = _Error/6 + _ErrorTracker.getComplexErrorAverage();

			//Proportional correction:
			_Proportional = _Kp * _Error;

			//Integral correction:
			_Integral = _Integral + (_Kp* ( _Ki * _CycleTime) * _Error);

			//Derivative control:
			_Derivative = _Kp * (_Kd/_CycleTime) * _ErrorVariation;

			//PID_Output
			_PIDOutput = _Proportional + _Derivative + _Integral;


			_ErrorTracker.addValue(_Error);
			
			// Perform Anti-reset windup?
			// if(m_bAntiResetWindup)
			// {
			// 	if(m_Output >= m_RangeMax-(m_ARWBound*m_Range))
			// 	{
			// 		m_Output = m_RangeMax-(m_ARWBound*m_Range);
			// 		m_Integral = m_OldIntegral;
			// 	}
			// 	else if(m_Output <= m_RangeMin+(m_ARWBound*m_Range))
			// 	{
			// 		m_Output = m_RangeMin+(m_ARWBound*m_Range);
			// 		m_Integral = m_OldIntegral;
			// 	}
			// }

			return _PIDOutput;
}