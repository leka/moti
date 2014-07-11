/*
FreeIMU.cpp - A libre and easy to use orientation sensing library for Arduino
Copyright (C) 2011-2012 Fabio Varesano <fabio at varesano dot net>

Development of this code has been supported by the Department of Computer Science,
Universita' degli Studi di Torino, Italy within the Piemonte Project
http://www.piemonte.di.unito.it/


This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <inttypes.h>
#include <stdint.h>
//#define DEBUG
#include "FreeIMU.h"
// #include "WireUtils.h"
#include "DebugUtils.h"

//#include "vector_math.h"

FreeIMU::FreeIMU() {
	gyro = ITG3200();

	// initialize quaternion
	q0 = 1.0f;
	q1 = 0.0f;
	q2 = 0.0f;
	q3 = 0.0f;
	exInt = 0.0;
	eyInt = 0.0;
	ezInt = 0.0;
	twoKp = twoKpDef;
	twoKi = twoKiDef;
	integralFBx = 0.0f,  integralFBy = 0.0f, integralFBz = 0.0f;
	lastUpdate = 0;
	now = 0;

	#ifndef CALIBRATION_H
		// initialize scale factors to neutral values
		acc_scale_x = 1;
		acc_scale_y = 1;
		acc_scale_z = 1;
		magn_scale_x = 1;
		magn_scale_y = 1;
		magn_scale_z = 1;
	#else
		// get values from global variables of same name defined in calibration.h
		acc_off_x = ::acc_off_x;
		acc_off_y = ::acc_off_y;
		acc_off_z = ::acc_off_z;
		acc_scale_x = ::acc_scale_x;
		acc_scale_y = ::acc_scale_y;
		acc_scale_z = ::acc_scale_z;
		magn_off_x = ::magn_off_x;
		magn_off_y = ::magn_off_y;
		magn_off_z = ::magn_off_z;
		magn_scale_x = ::magn_scale_x;
		magn_scale_y = ::magn_scale_y;
		magn_scale_z = ::magn_scale_z;
	#endif
}

void FreeIMU::init() {
	init(FIMU_ACC_ADDR, FIMU_ITG3200_DEF_ADDR, false);
}

void FreeIMU::init(bool fastmode) {
	init(FIMU_ACC_ADDR, FIMU_ITG3200_DEF_ADDR, fastmode);
}


/**
 * Initialize the FreeIMU I2C bus, sensors and performs gyro offsets calibration
*/
void FreeIMU::init(int acc_addr, int gyro_addr, bool fastmode) {
	delay(5);

	// disable internal pullups of the ATMEGA which Wire enable by default
	#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
	// deactivate internal pull-ups for twi
	// as per note from atmega8 manual pg167
	cbi(PORTC, 4);
	cbi(PORTC, 5);
	#else
	// deactivate internal pull-ups for twi
	// as per note from atmega128 manual pg204
	cbi(PORTD, 0);
	cbi(PORTD, 1);
	#endif

	if(fastmode) { // switch to 400KHz I2C - eheheh
	 TWBR = ((F_CPU / 400000L) - 16) / 2; // see twi_init in Wire/utility/twi.c
	}

	acc.init(acc_addr);

	// init ITG3200
	gyro.init(gyro_addr);
	delay(1000);
	// calibrate the ITG3200
	gyro.zeroCalibrate(128,5);

	// zero gyro
	zeroGyro();
}

/**
 * Populates raw_values with the raw_values from the sensors
*/
void FreeIMU::getRawValues(int * raw_values) {
	acc.readAccel(&raw_values[0], &raw_values[1], &raw_values[2]);
	gyro.readGyroRaw(&raw_values[3], &raw_values[4], &raw_values[5]);
}


/**
 * Populates values with calibrated readings from the sensors
*/
void FreeIMU::getValues(float * values) {
	int accval[3];
	acc.readAccel(&accval[0], &accval[1], &accval[2]);
	values[0] = (float) accval[0];
	values[1] = (float) accval[1];
	values[2] = (float) accval[2];
	gyro.readGyro(&values[3]);


	// #warning Accelerometer calibration active: have you calibrated your device?
	// remove offsets and scale accelerometer (calibration)
	values[0] = (values[0] - acc_off_x) / acc_scale_x;
	values[1] = (values[1] - acc_off_y) / acc_scale_y;
	values[2] = (values[2] - acc_off_z) / acc_scale_z;
}


/**
 * Computes gyro offsets
*/
void FreeIMU::zeroGyro() {
	const int totSamples = 3;
	int raw[11];
	float tmpOffsets[] = {0,0,0};

	for (int i = 0; i < totSamples; i++){
		getRawValues(raw);
		tmpOffsets[0] += raw[3];
		tmpOffsets[1] += raw[4];
		tmpOffsets[2] += raw[5];
	}

	gyro_off_x = tmpOffsets[0] / totSamples;
	gyro_off_y = tmpOffsets[1] / totSamples;
	gyro_off_z = tmpOffsets[2] / totSamples;
}


/**
 * Quaternion implementation of the 'DCM filter' [Mayhony et al].  Incorporates the magnetic distortion
 * compensation algorithms from Sebastian Madgwick's filter which eliminates the need for a reference
 * direction of flux (bx bz) to be predefined and limits the effect of magnetic distortions to yaw
 * axis only.
 *
 * @see: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
*/
void  FreeIMU::AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float halfex = 0.0f, halfey = 0.0f, halfez = 0.0f;
	float qa, qb, qc;

	// Auxiliary variables to avoid repeated arithmetic
	q0q0 = q0 * q0;
	q0q1 = q0 * q1;
	q0q2 = q0 * q2;
	q0q3 = q0 * q3;
	q1q1 = q1 * q1;
	q1q2 = q1 * q2;
	q1q3 = q1 * q3;
	q2q2 = q2 * q2;
	q2q3 = q2 * q3;
	q3q3 = q3 * q3;

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if((ax != 0.0f) && (ay != 0.0f) && (az != 0.0f)) {
	float halfvx, halfvy, halfvz;

	// Normalise accelerometer measurement
	recipNorm = invSqrt(ax * ax + ay * ay + az * az);
	ax *= recipNorm;
	ay *= recipNorm;
	az *= recipNorm;

	// Estimated direction of gravity
	halfvx = q1q3 - q0q2;
	halfvy = q0q1 + q2q3;
	halfvz = q0q0 - 0.5f + q3q3;

	// Error is sum of cross product between estimated direction and measured direction of field vectors
	halfex += (ay * halfvz - az * halfvy);
	halfey += (az * halfvx - ax * halfvz);
	halfez += (ax * halfvy - ay * halfvx);
	}

	// Apply feedback only when valid data has been gathered from the accelerometer or magnetometer
	if(halfex != 0.0f && halfey != 0.0f && halfez != 0.0f) {
	// Compute and apply integral feedback if enabled
	if(twoKi > 0.0f) {
		integralFBx += twoKi * halfex * (1.0f / sampleFreq);  // integral error scaled by Ki
		integralFBy += twoKi * halfey * (1.0f / sampleFreq);
		integralFBz += twoKi * halfez * (1.0f / sampleFreq);
		gx += integralFBx;  // apply integral feedback
		gy += integralFBy;
		gz += integralFBz;
	}
	else {
		integralFBx = 0.0f; // prevent integral windup
		integralFBy = 0.0f;
		integralFBz = 0.0f;
	}

	// Apply proportional feedback
	gx += twoKp * halfex;
	gy += twoKp * halfey;
	gz += twoKp * halfez;
	}

	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));   // pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}


/**
 * Populates array q with a quaternion representing the IMU orientation with respect to the Earth
 *
 * @param q the quaternion to populate
*/
void FreeIMU::getQ(float * q) {
	float val[9] = { 0.f };
	getValues(val);

	/*DEBUG_PRINT(val[3] * M_PI/180);
	DEBUG_PRINT(val[4] * M_PI/180);
	DEBUG_PRINT(val[5] * M_PI/180);
	DEBUG_PRINT(val[0]);
	DEBUG_PRINT(val[1]);
	DEBUG_PRINT(val[2]);
	DEBUG_PRINT(val[6]);
	DEBUG_PRINT(val[7]);
	DEBUG_PRINT(val[8]);*/

	now = micros();
	sampleFreq = 1.0 / ((now - lastUpdate) / 1000000.0);
	lastUpdate = now;

	AHRSupdate(val[3] * M_PI/180, val[4] * M_PI/180, val[5] * M_PI/180, val[0], val[1], val[2]);

	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
}


/**
 * Returns the Euler angles in radians defined in the Aerospace sequence.
 * See Sebastian O.H. Madwick report "An efficient orientation filter for
 * inertial and intertial/magnetic sensor arrays" Chapter 2 Quaternion representation
 *
 * @param angles three floats array which will be populated by the Euler angles in radians
*/
void FreeIMU::getEulerRad(float * angles) {
	float q[4]; // quaternion
	getQ(q);

	angles[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1); // psi
	angles[1] = -asin(2 * q[1] * q[3] + 2 * q[0] * q[2]); // theta
	angles[2] = atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1); // phi
}


/**
 * Returns the Euler angles in degrees defined with the Aerospace sequence.
 * See Sebastian O.H. Madwick report "An efficient orientation filter for
 * inertial and intertial/magnetic sensor arrays" Chapter 2 Quaternion representation
 *
 * @param angles three floats array which will be populated by the Euler angles in degrees
*/
void FreeIMU::getEuler(float * angles) {
	getEulerRad(angles);
	arr3_rad_to_deg(angles);
}


/**
 * Returns the yaw pitch and roll angles, respectively defined as the angles in radians between
 * the Earth North and the IMU X axis (yaw), the Earth ground plane and the IMU X axis (pitch)
 * and the Earth ground plane and the IMU Y axis.
 *
 * @note This is not an Euler representation: the rotations aren't consecutive rotations but only
 * angles from Earth and the IMU. For Euler representation Yaw, Pitch and Roll see FreeIMU::getEuler
 *
 * @param ypr three floats array which will be populated by Yaw, Pitch and Roll angles in radians
*/
void FreeIMU::getYawPitchRollRad(float * ypr) {
	float q[4]; // quaternion
	float gx, gy, gz; // estimated gravity direction
	getQ(q);

	gx = 2 * (q[1]*q[3] - q[0]*q[2]);
	gy = 2 * (q[0]*q[1] + q[2]*q[3]);
	gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];

	ypr[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1);
	ypr[1] = atan(gx / sqrt(gy*gy + gz*gz));
	ypr[2] = atan(gy / sqrt(gx*gx + gz*gz));
}

void FreeIMU::getYawPitchRollEulerRad(float * ypr, float * euler) {
	float q[4]; // quaternion
	float gx, gy, gz; // estimated gravity direction
	getQ(q);

	gx = 2 * (q[1]*q[3] - q[0]*q[2]);
	gy = 2 * (q[0]*q[1] + q[2]*q[3]);
	gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];

	ypr[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1); // yaw
	ypr[1] = atan(gx / sqrt(gy*gy + gz*gz)); // pitch
	ypr[2] = atan(gy / sqrt(gx*gx + gz*gz)); // roll

	euler[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1); // psi
	euler[1] = -asin(2 * q[1] * q[3] + 2 * q[0] * q[2]); // theta
	euler[2] = atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1); // phi
}


/**
 * Returns the yaw pitch and roll angles, respectively defined as the angles in degrees between
 * the Earth North and the IMU X axis (yaw), the Earth ground plane and the IMU X axis (pitch)
 * and the Earth ground plane and the IMU Y axis.
 *
 * @note This is not an Euler representation: the rotations aren't consecutive rotations but only
 * angles from Earth and the IMU. For Euler representation Yaw, Pitch and Roll see FreeIMU::getEuler
 *
 * @param ypr three floats array which will be populated by Yaw, Pitch and Roll angles in degrees
*/
void FreeIMU::getYawPitchRoll(float * ypr) {
	getYawPitchRollRad(ypr);
	arr3_rad_to_deg(ypr);
}


/**
 * Converts a 3 elements array arr of angles expressed in radians into degrees
*/
void arr3_rad_to_deg(float * arr) {
	arr[0] *= 180.0f / M_PI;
	arr[1] *= 180.0f / M_PI;
	arr[2] *= 180.0f / M_PI;
}


/**
 * Fast inverse square root implementation
 * @see http://en.wikipedia.org/wiki/Fast_inverse_square_root
*/
float invSqrt(float number) {
	volatile long i;
	volatile float x, y;
	volatile const float f = 1.5f;

	x = number * 0.5f;
	y = number;
	i = * ( long * ) &y;
	i = 0x5f375a86 - ( i >> 1 );
	y = * ( float * ) &i;
	y = y * ( f - ( x * y * y ) );
	return y;
}



