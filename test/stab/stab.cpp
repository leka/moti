#define serial Serial

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
#include "Motor.h"

int _LOOP_TIME = 10;
int _MARGE = 5;
int _ORIGIN_PITCH = 0;

Sensors sensors;

Led mood = Led(11,12,13);

Motor right_motor = Motor(7,6);
Motor left_motor = Motor(4,5);

int pitch = 0;

//avance = 1, recule = -1, arret = 0
int ordre_moteur = 0;
int etat_moteurs = 0;
int compteur = 0;

static WORKING_AREA(waMainLoop, 1000);

static msg_t MainLoop(void *arg)
{
	(void)arg;

	systime_t timeT = chTimeNow();

	mood.shine(0,0,255);

	while (TRUE) {
		timeT += MS2ST(50);
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
				right_motor.spin(0, 200);
				left_motor.spin(0, 200);
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
				right_motor.spin(1, 200);
				left_motor.spin(1,200);
				mood.shine(255,0,0);
			}
		}

		//chSemSignal(&sens);
		chThdSleepUntil(timeT);
	}
	return 0;
}

void chSetup() {
	chThdCreateStatic(waMainLoop, sizeof(waMainLoop),NORMALPRIO, MainLoop, NULL);
}


void setup() {
	serial.begin(115200);
	sensors.init();
	chBegin(chSetup);
	while(1) {
	}
}

void loop() {
	// nothing to do here
}
