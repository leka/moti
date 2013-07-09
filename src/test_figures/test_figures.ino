//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include "Arduino.h"

#include "Moti.h"

#include "RGBLED.h"

#include <Wire.h>

#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>


int theta, delta, mcycle, angle;



MOTI Moti = MOTI();

void MotorSpinRightAngle(int spin) { // Angle quelconque 
	
	Moti.checkGyroscope();
	
	mcycle = int(spin/360);
	spin = spin%360;

	
	for (int i = 0; i < mcycle; i++) {

		theta = Moti.getYPR(0);
		delta = 0;
		
		while (abs(delta - 360) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < 360){ Moti.spinRight(); }
	
		else { Moti.spinLeft(); }

		angle = Moti.getYPR(0);

		if (angle < theta){angle = angle + 360;}
		
		delta = abs(angle - theta);
	
		}

	
	}


	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;
	

	while (abs(delta - spin) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < spin){ Moti.spinRight(); }
	
		else { Moti.spinLeft(); }

		angle = Moti.getYPR(0);

		if (angle < theta){angle = angle + 360;}
		delta = abs(angle - theta);

	}

	Moti.stop();

	}


void MotorSpinLeftAngle(int spin) {  // Angle quelconque 

	Moti.checkGyroscope();
	
	mcycle = int(spin/360);
	spin = spin%360;

	
	for (int i = 0; i < mcycle; i++) {

		theta = Moti.getYPR(0);
		delta = 0;
		
		while (abs(delta - 360) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < 360){ Moti.spinLeft(); }
	
		else { Moti.spinRight(); }

		angle = Moti.getYPR(0);

		if (angle > theta){angle = angle - 360;}
		
		delta = abs(angle - theta);
	
		}

	
	}


	Moti.checkGyroscope();
	theta = Moti.getYPR(0);
	delta = 0;

	
	while (abs(delta - spin) > 5) { 	

		Moti.checkGyroscope();	

		if(delta < spin){ Moti.spinLeft(); }
	
		else { Moti.spinRight(); }

		angle = Moti.getYPR(0);

		if (angle > theta){angle = angle - 360;}
		
		delta = abs(angle - theta);

	}

	Moti.stop();
	}


void Square(int distance) {

	Moti.goForward();
	delay(100*distance); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	
	MotorSpinRightAngle(90);
	
	Moti.goForward();
	delay(100*distance); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);

	MotorSpinRightAngle(90);
	
	Moti.goForward();
	delay(100*distance); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	
	MotorSpinRightAngle(90);
	
	Moti.goForward();
	delay(100*distance); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	
	MotorSpinRightAngle(90);

	}


void Rectangle(int distance1, int distance2) {

	Moti.goForward();
	delay(100*distance1); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	MotorSpinRightAngle(90);
	Moti.goForward();
	delay(100*distance2); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	MotorSpinRightAngle(90);
	Moti.goForward();
	delay(100*distance1); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	MotorSpinRightAngle(90);
	Moti.goForward();
	delay(100*distance2); 			// Le coefficient 100 depend de la vitesse lineaire du moteur en fonction de distance en cm.            
	Moti.stop();
	delay(500);
	MotorSpinRightAngle(90);

}

void Cercle (int radius, int Cspeed) {

Cspeed = constrain(Cspeed, Moti.getMotorMinSpeed(), Moti.getMotorMaxSpeed());

int _coeff = 1 - (0.1*0.1*Cspeed/255)/radius ;   // On considere distance entre roues = 0.1 et vitesse lineaire a 255 comme 0.1 m/s. 

Moti.checkGyroscope();
theta = Moti.getYPR(0);
delta = 360;

Moti.spinLeftWheel(Cspeed, 0);
Moti.spinRightWheel(Cspeed * _coeff, 0); 	   // Radius egale a: distance entre roues * vitesse lineaire maximun / (1 - coeff)
Moti.setMovingState(true);
delay (1000);

while (abs(delta) > 5){

Moti.checkGyroscope();
delta = Moti.getYPR(0) - theta;


}


Moti.stop();

}

void Croix (int distance) {

Moti.goForward();
delay(100*distance);
Moti.goBackward();
delay(100*distance);
MotorSpinRightAngle(90);      // On marche une distance en centimetre, on revient et apres on tourne 90 degrees.
Moti.goForward();
delay(100*distance);
Moti.goBackward();
delay(100*distance);
MotorSpinRightAngle(90);
Moti.goForward();
delay(100*distance);
Moti.goBackward();
delay(100*distance);
MotorSpinRightAngle(90);
Moti.goForward();
delay(100*distance);
Moti.goBackward();
delay(100*distance);
MotorSpinRightAngle(90);

}

void Spirale (int coeff, int Sspeed) {

Sspeed = constrain(Sspeed, Moti.getMotorMinSpeed(), Moti.getMotorMaxSpeed());
coeff = constrain(coeff, 1, 10);

for (int i = 2; i <= coeff ; i++) {
Moti.spinLeftWheel(Sspeed, 0);
Moti.spinRightWheel(Sspeed * (i*0.1), 0); 	   // Radius egale a: distance entre roues * vitesse lineaire maximun / (1 - coeff)

Moti.setMovingState(true);

delay(2000); }   // Temps egale a 2*pi*Radius/Vitesse, d'où vitesse est egale a 0.1*speed/255

Moti.stop();

}

void Behaviour (){

Moti.blinkLed(0,0,255,5,250);
Moti.printRgbColor(0,0,255);
Square(20);	
Moti.blinkLed(0,0,255,5,250);
Moti.printRgbColor(0,0,255);
Square(60);	

Moti.blinkLed(255,0,0,5,250);
Moti.printRgbColor(255, 0, 0);		
Spirale (7,255);
Moti.blinkLed(255,0,0,5,250);
Moti.printRgbColor(255, 0, 0);		
Spirale (10,255);

Moti.blinkLed(0,255,0,5,250);
Moti.printRgbColor(0, 255, 0);
Croix(30);
Moti.blinkLed(0,255,0,5,250);
Moti.printRgbColor(0, 255, 0);		
Croix(50);

Moti.blinkLed(0,255,255,5,250);
Moti.printRgbColor(0,255,255);			
Rectangle(20,40);	
Moti.blinkLed(0,0,255,5,250);
Moti.printRgbColor(0,0,255);
Rectangle(60,100);	

Moti.blinkLed(255,0,255,5,250);
Moti.printRgbColor(255, 0, 255);		
Cercle(40,255);
Moti.blinkLed(255,0,255,5,250);
Moti.printRgbColor(255, 0, 255);		
Cercle(70,255);

}


//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
}



//######//
// LOOP //
//######//

void loop() {
	

delay(2000);
Behaviour();

}

