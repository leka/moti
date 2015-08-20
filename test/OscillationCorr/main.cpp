#include <Arduino.h>
#include <Wire.h>

#include "ChibiOS_AVR.h"
// #include "Moti.h"
#include "Sensors.h"
#include "Motion.h"
#include "DriveSystem.h"

float PWMtoLinVel(int PWMdesired){
int RPM = 260;		// rotation per min of the motor
float r = 0.02;	// radius of the wheels
float d = 0.06;	// distance wheeks-center
float R = 0.09;	//  radius of the shell
float phid;
float Vel;

phid = RPM * PWMdesired * 2 * 3.141592 /(255 * 60); // fait en une ligne au lieu de deux, a checker!!!!!!!!!
Vel = r * phid * R / d;				  // pareil
return Vel;
}

int LinVeltoPWM (float Vel){
int RPM = 260;		// rotation per min of the motor
float r = 0.02;	// radius of the wheels
float d = 0.06;	// distance wheeks-center
float R = 0.09;	//  radius of the shell
float phid;
float phiMax;
float PWM;

phiMax = RPM * 2 * 3.141592;
phid = (Vel * d) / (r*R) ; // fait en une ligne au lieu de deux, a checker!!!!!!!!!
PWM = phid * 255 / phiMax;				  // pareil
// Serial.print("PWM ");
// Serial.println(PWM);
int PWMint = static_cast<int>(PWM);
// Serial.print("PWMint ");
// Serial.println(PWMint);
return PWMint;
}

void mainThread() {
// DECLARATION
	int PWM;
	float	deltaT;
	float	Acc;
	float	DPitch;
	float	Vel;
	float  Moy;
	float	SP;
	float	Vosc;

//INITIALIZATION
	Sensors::init();
	Sensors::start();
	int PWMdesired = 200;
	float SumAcc = 0;
	float PitchOld = Sensors::getGyrP();
	float timeOld = 0;
	float 	MoySum = 0;
	float cte = 9.81 * 4 / 1024;
	bool SpReach = TRUE;
	int i = 1;
	
	while (TRUE) {
		deltaT = (millis()-timeOld)*0.001; //DeltaT a chaque instant
		 Serial.print("deltaT :");
		// Serial.println(deltaT);
		Acc = Sensors::getAccX();
		Acc =  Acc * cte;    // Get ACC
		 Serial.print("Acc :");
		// Serial.println(Sensors::getAccX());
		// Serial.println(Acc);
		SumAcc =  (deltaT*Acc) + SumAcc;    // Integration of Acc SumAcc 
		 Serial.print("SumAcc :");
		// Serial.println(SumAcc);
		DPitch = ((Sensors::getGyrP())-PitchOld)/deltaT; // prime derivative of pitch

		Vel = SumAcc + DPitch;
		MoySum = MoySum + Vel;
		Moy = MoySum / i;
		 Serial.print("sp :");
		// Serial.println(SP);

		SP = PWMtoLinVel(PWMdesired);
		 Serial.print("sp :");
		// Serial.println(SP);
		if ((Moy <= SP) && (SpReach==TRUE)){
			 Serial.println("Vosc=Moy");
			Vosc = Moy;
		}
		else {
			// Serial.println("Vosc no Moy");
			Vosc = (2 * SP) - Moy;
			SpReach = 0;
		}

		PWM = LinVeltoPWM (Vosc);
		// Serial.println(PWM);

		DriveSystem::go(FORWARD, 200);

		i++;
		timeOld = millis();
		PitchOld = Sensors::getGyrP();

		waitMs(50);
	}
}




void loop() { }

int main(void) {
	init();

	Serial.begin(115200);
	while (!Serial);

		// Serial1.begin(115200);
		// while (!Serial1);

	Wire.begin();
	delay(5000);

	chBegin(mainThread);

	while(1);

	return 0;
}