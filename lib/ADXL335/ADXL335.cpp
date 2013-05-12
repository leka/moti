/*
  ADXL335.cpp - Library for reading the ADXL335 Accelerometer
  Created by Derek Chafin, September 14, 2011
  Released into the public domain.
*/

#include "ADXL335.h"

ADXL335::ADXL335(int pin_x, int pin_y, int pin_z, float aref)
{
  _aref = aref;
  _pin_x = pin_x;
  _pin_y = pin_y;
  _pin_z = pin_z;
  _mvG = aref / 10.0;
  _bias = aref / 2.0;
  _rad2deg = 180.0 / M_PI;
}

//begin private methods
float ADXL335::geta2d(float gx, float gy)
{
  float a;
  
  a = gx * gx;
  a = fma(gy,gy,a);
  
  return sqrt(a);
}

//gets the magnitude of the 3d vector
//the formula is a^2 = x^2 + y^2 + z^2
float ADXL335::geta3d(float gx, float gy, float gz)
{
  float a;
  
  //use floating point multiply-add cpu func
  //sometimes we get better precision
  a = gx * gx;
  a = fma(gy,gy,a);
  a = fma(gz,gz,a);
  
  return sqrt(a);
}

void ADXL335::processDeadzone(float* gv)
{
  if (*gv < _deadzone && *gv > -_deadzone)
  {
    *gv = 0.0;
  }
}

float ADXL335::getGravity(int reading)
{  
  float voltage = reading * _aref;
  voltage /= 1024.0;

  //minus the zero g bias 
  //then divide by mv/g
  //which when Vs = 3.3V, V/g = 0.330
  float gv = (voltage - _bias) / _mvG;
  
  //minus the null zone
  processDeadzone(&gv);
  
  return gv;
}

float ADXL335::_getRho(float ax, float ay, float az)
{
  return geta3d(_xg,_yg,_zg);
}

float ADXL335::_getPhi(float ax, float ay, float az)
{
  return atan2(ay, ax) * _rad2deg;  
}

float ADXL335::_getTheta(float ax, float ay, float az)
{
  float rho = _getRho(ax, ay, az);
  
  if (rho == 0.0)
    return NAN;
  else
    return acos(az / rho) * _rad2deg;
}

//end private methods


//begin public methods
void ADXL335::setThreshold(float deadzone)
{
  _deadzone = deadzone;
}

//gets whether the device is in free fall
boolean ADXL335::getFreefall()
{
  //if all three vectors read zero then return true, otherwise; false.
  return _xg == 0.0 && _yg == 0.0 && _zg == 0.0;
}

float ADXL335::getX()
{
  return _xg;
}

float ADXL335::getY()
{
  return _yg;
}

float ADXL335::getZ()
{
  return _zg;
}

float ADXL335::getRho()
{
  return _getRho(_xg,_yg,_zg);
}

float ADXL335::getPhi()
{
  return _getPhi(_xg,_yg,_zg);
}

float ADXL335::getTheta()
{
  return _getTheta(_xg,_yg,_zg);
}

void ADXL335::update()
{
  _xg = getGravity(analogRead(_pin_x));
  _yg = getGravity(analogRead(_pin_y));
  _zg = getGravity(analogRead(_pin_z));
}

//end public methods
