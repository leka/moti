#include <Wire.h>
#include <Arduino.h>

#include "ChibiOS_AVR.h"
#include "Serial.h"
#include "Tools.h"
#include "CommunicationUtils.h"
#include "DebugUtils.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "FreeIMU.h"
#include "Sensors.h"
#include "Led.h"
#include "DriveSystem.h"
#include "Motor.h"

int _LOOP_TIME = 10;
int _MARGE = 5;
int _ORIGIN_PITCH = 0;

Sensors sensors;
DriveSystem robot;

Led mood = Led(11,12,13);

int pitch = 0;

//avance = 1, recule = -1, arret = 0
int ordre_moteur = 0;
int etat_moteurs = 0;
int compteur = 0;

/* static WORKING_AREA(waMainLoop, 1000);

static msg_t MainLoop(void *arg) 
{
	(void)arg;

	systime_t time = chTimeNow();
	
	mood.shine(0,0,255);

	while (TRUE) {
		time += MS2ST(50);
		sensors.read();
		pitch = sensors.getYPR(1);
		compteur++;
		if(pitch > _ORIGIN_PITCH + _MARGE){
			ordre_moteur = 1;
		}
		else if(pitch < _ORIGIN_PITCH + _MARGE){
			ordre_moteur = -1;
		}
		else{
			ordre_moteur = 0;
		}
		
		if (compteur == 5){
			compteur = 0;
			if(ordre_moteur==1 && etat_moteurs != 1) {
				etat_moteurs = 1;
				right_motor.spin(0, 100);
				left_motor.spin(0, 100);
				mood.shine(0,255,0);
			}
			if(ordre_moteur==0 && etat_moteurs != 0){
				etat_moteurs = 0;
				right_motor.stop();
				left_motor.stop();
				mood.shine(0,0,255);
			}
			if(ordre_moteur==-1 && etat_moteurs !=-1){
				etat_moteurs = -1;
				right_motor.spin(1, 100);
				left_motor.spin(1,100);
				mood.shine(255,0,0);
			}
		}
		
		//chSemSignal(&sens);
		chThdSleepUntil(time);
	}
	return 0;
}
*/

void chSetup() {
	//chThdCreateStatic(waMainLoop, sizeof(waMainLoop),NORMALPRIO, MainLoop, NULL);

	chThdSleepMilliseconds(5000);

	DriveSystem robot = DriveSystem();

	float x, y;

	uint32_t lastSpin = 0, elapsedTime = 0;

	Direction dir;

	while (TRUE) {
		/** STABILIZATION **/

		sensors.read();
		x = sensors.getXYZ(0);
		y = sensors.getXYZ(1);

		Serial.println(x);
		Serial.println(y);
		Serial.println("A");

		elapsedTime = chTimeNow() - lastSpin;

		if ((elapsedTime > 350) && (abs(y) > 90) && (abs(y - 20) > abs(x))) {
			robot.spin(sensors, RIGHT, 110, 90);
			lastSpin = chTimeNow();
		}

		while (abs(x) > 50) {
			sensors.read();
			x = sensors.getXYZ(0);
			
			Serial.print(x);
			Serial.print(' ');
			Serial.println(y);
				
			if (x >= 0)
				dir = BACK;
			else
				dir = FORTH;

			robot.launch(dir, 110, 0);
		}

		robot.stop(0);

		/**********/
	}
}


void setup() {
	Serial.begin(115200);
	sensors.init();

	Serial.println("111");

	chBegin(chSetup);
	
	//while (1) {
		
	//}
}

void loop() {
	// nothing to do here
}
