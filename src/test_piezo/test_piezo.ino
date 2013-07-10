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


#define c 1876 //       261 Hz       3830      	
#define d 1663 //       294 Hz       3400       	
#define e 1482 //       329 Hz       3038       	
#define f 1397 //       349 Hz       2864       	
#define g 1241 //       392 Hz       2550        	
#define a 1102 //       440 Hz       2272        // Valeur changé en fonction des mesures	
#define b 981  //       493 Hz       2028       	
#define C 923  //       523 Hz       1912       

#define fc 261 //       261 Hz       3830      	
#define fd 294 //       294 Hz       3400       	
#define fe 329 //       329 Hz       3038       	
#define ff 349 //       349 Hz       2864       	
#define fg 392 //       392 Hz       2550        	
#define fa 440 //       440 Hz       2272        // Valeur changé en fonction des mesures	
#define fb 493 //       493 Hz       2028       	
#define fC 523 //       523 Hz       1912 


MOTI Moti = MOTI();

int port = 3;

int sing [24][2] = {c, 4, d, 4, e, 4, f, 4, f, 4, f, 4, c, 4, d, 4, c, 4, d, 4, d, 4, d, 4, c, 4, g, 4, f, 4, e, 4, e, 4, e, 4, c, 4, d, 4, e, 4, f, 4, f, 4, f, 4 };

void sound(int time, int repeat) {

	for (int i = 1; i <= (repeat - 2) ; i++) {
		analogWrite(port,255);
	 	delayMicroseconds(time);
		analogWrite(port,0);
		delayMicroseconds(time);
	}

	delayMicroseconds(4*time);

}

void music(int sing[24][2]){

	for (int i = 0; i<=23; i++){

		sound(sing[i][0]/sing[i][1], 250000/(sing[i][0]));

	}

}

void Note (int note, int niveau, int division){
	delayMicroseconds(10000);
	sound(note/niveau,(490000/note)/division);
}

void Note (int note, int division){
	delayMicroseconds(10000);
	sound(note,(490000/note)/division);
}

void Note (int note){
	delayMicroseconds(10000);
	sound(note,(490000/note));
}

void music (int power, int repeat) { }

//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
	pinMode(port,OUTPUT);
}



//######//
// LOOP //
//######//

void loop() {

//sinus (port, b, 87);

music(sing);

}

