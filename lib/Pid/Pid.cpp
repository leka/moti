/**********************************************************************************************
 * Arduino PID Library - Version 1.0.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include "Arduino.h"
#include <Pid.h>

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
Pid::Pid(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int ControllerDirection)
{

    _myOutput = Output;
    _myInput = Input;
    _mySetpoint = Setpoint;
	 _inAuto = false;

	Pid::setOutputLimits(0, 255);				//default output limit corresponds to
												//the arduino pwm limits

    _sampleTime = 100;							//default Controller Sample Time is 0.1 seconds

    Pid::setControllerDirection(ControllerDirection);
    Pid::setTunings(Kp, Ki, Kd);

    _lastTime = millis()-_sampleTime;
}


/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
bool Pid::compute()
{
   if(!_inAuto) return false;
   unsigned long now = millis();
   unsigned long timeChange = (now - _lastTime);
   if(timeChange>=_sampleTime)
   {
      /*Compute all the working error variables*/
	  double input = *_myInput;
      double error = *_mySetpoint - input;
      _ITerm+= (_Ki * error);
      if(_ITerm > _outMax) _ITerm= _outMax;
      else if(_ITerm < _outMin) _ITerm= _outMin;
      double dInput = (input - _lastInput);

      /*Compute PID Output*/
      double output = _Kp * error + _ITerm- _Kd * dInput;

	  if(output > _outMax) output = _outMax;
      else if(output < _outMin) output = _outMin;
	  *_myOutput = output;

      /*Remember some variables for next time*/
      _lastInput = input;
      _lastTime = now;
	  return true;
   }
   else return false;
}


/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void Pid::setTunings(double Kp, double Ki, double Kd)
{
   if (Kp<0 || Ki<0 || Kd<0) return;

   _dispKp = Kp; _dispKi = Ki; _dispKd = Kd;

   double _sampleTimeInSec = ((double)_sampleTime)/1000;
   _Kp = Kp;
   _Ki = Ki * _sampleTimeInSec;
   _Kd = Kd / _sampleTimeInSec;

  if(_controllerDirection == REVERSE)
   {
      _Kp = (0 - _Kp);
      _Ki = (0 - _Ki);
      _Kd = (0 - _Kd);
   }
}

/* Set_sampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void Pid::setSampleTime(int New_sampleTime)
{
   if (New_sampleTime > 0)
   {
      double ratio  = (double)New_sampleTime
                      / (double)_sampleTime;
      _Ki *= ratio;
      _Kd /= ratio;
      _sampleTime = (unsigned long)New_sampleTime;
   }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void Pid::setOutputLimits(double Min, double Max)
{
   if(Min >= Max) return;
   _outMin = Min;
   _outMax = Max;

   if(_inAuto)
   {
	   if(*_myOutput > _outMax) *_myOutput = _outMax;
	   else if(*_myOutput < _outMin) *_myOutput = _outMin;

	   if(_ITerm > _outMax) _ITerm= _outMax;
	   else if(_ITerm < _outMin) _ITerm= _outMin;
   }
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void Pid::setMode(int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto == !_inAuto)
    {  /*we just went from manual to auto*/
        Pid::Initialize();
    }
    _inAuto = newAuto;
}

/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void Pid::Initialize()
{
   _ITerm = *_myOutput;
   _lastInput = *_myInput;
   if(_ITerm > _outMax) _ITerm = _outMax;
   else if(_ITerm < _outMin) _ITerm = _outMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void Pid::setControllerDirection(int Direction  )
{
   if(_inAuto && Direction != _controllerDirection)
   {
	  _Kp = (0 - _Kp);
      _Ki = (0 - _Ki);
      _Kd = (0 - _Kd);
   }
   _controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
double Pid::getKp(){ return  _dispKp; }
double Pid::getKi(){ return  _dispKi;}
double Pid::getKd(){ return  _dispKd;}
int Pid::getMode(){ return  _inAuto ? AUTOMATIC : MANUAL;}
int Pid::getDirection(){ return _controllerDirection;}

