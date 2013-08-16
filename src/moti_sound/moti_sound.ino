//######################################################################//
//	MOTI SOFTWARE v2.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//

/**
 * @file moti_sound.ino
 * @brief moti_sound.ino is used for define the robot behaviours need to draw one figure.
 * @author Luan Ferrari
 * @version 1.0
 */

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
#define a 1102 //       440 Hz       2272        // Valeurs changés en fonction des mesures des temps en microseconds pour un son parfaitement en frequence desiré. 	
#define b 981  //       493 Hz       2028       	
#define C 923  //       523 Hz       1912       

#define fc 261 //       261 Hz       3830      	
#define fd 294 //       294 Hz       3400       	
#define fe 329 //       329 Hz       3038       	
#define ff 349 //       349 Hz       2864       	
#define fg 392 //       392 Hz       2550        	
#define fa 440 //       440 Hz       2272        // Valeurs changés en fonction des mesures des temps en microseconds pour un son parfaitement en frequence desiré. 	
#define fb 493 //       493 Hz       2028       	
#define fC 523 //       523 Hz       1912 


MOTI Moti = MOTI();

int port = 3;



// Songs Informations #Constants !!!


	// SUPER MARIO BROS (Array de Frequence)  
	int melody_Mario [156] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
	int duration_Mario [] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
	int pause_Mario [] = {150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575}; 	

		
	// DO RE MI FA (Fonction de Luan)

	int melody_DoReMiFa_temps [24] = {c, d, e, f, f, f, c, d, c, d, d, d, c, g, f, e, e, e, c, d, e, f, f, f};
	int tone_DoReMiFa [] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	float temps_DoReMiFa [] = {0.6, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

    float sing_DoReMiFa [24][3] = {c, 2, 0.2, d, 2, 0.2, e, 2, 0.2, f, 2, 0.2, f, 2, 0.2, f, 2, 0.2, c, 2, 0.2, d, 2, 0.2, c, 2, 0.2, d, 2, 0.2, d, 2, 0.2, d, 2, 0.2, c, 2, 0.2, g, 2, 0.2, f, 2, 0.2, e, 2, 0.2, e, 2, 0.2, e, 2, 0.2, c, 2, 0.2, d, 2, 0.2, e, 2, 0.2, f, 2, 0.2, f, 2, 0.2, f, 2, 0.2};


	// Musique 1 (Fonction de Luan)

	int melody_Music1 [] = {c, b, a, g, e, d, b, c, b, a, g, e, d, e, d, e, c, g, a, c, d, e, d, e, e, d, e, c, a, c, d, c, c, b, c, b, c, g, e, a, g, a, g, d, e, g, d, e, e, d, c, d, e, d, e};
	int tone_Music1 [] = {2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	float temps_Music1 [] = {2, 0.5, 2, 0.5, 2, 2, 0.5, 2, 0.5, 2, 0.5, 2, 2, 1, 0.25, 1, 2, 0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 2, 1, 0.5, 1, 2, 1, 0.5, 0.5, 2, 2, 0.5, 0.5, 0.25, 0.25, 0.5, 0.25, 1, 0.25, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1, 1, 0.25, 1, 1, 1, 1};

	float sing_Music1 [55][3] = {c, 2, 2, b, 1, 0.5, a, 1, 2, g, 1, 0.5, e, 1, 2, d, 1, 2, b, 1, 0.5, c, 2, 2, b, 1, 0.5, a, 1, 2, g, 1, 0.5, e, 1, 2, d, 1, 2, e, 2, 1, d, 2, 0.25, e, 2, 1, c, 2, 2, g, 1, 0.5, a, 1, 0.5, c, 2, 0.5, d, 2, 0.5, e, 2, 0.5, d, 2, 0.25, e, 2, 2, e, 2, 1, d, 2, 0.5, e, 2, 1, c, 2, 2, a, 1, 1, c, 2, 0.5, d, 2, 0.5, c, 2, 2, c, 2, 2, b, 1, 0.5, c, 2, 0.5, b, 1, 0.25, c, 2, 0.25, g, 1, 0.5, e, 1, 0.25, a, 1, 1, g, 1, 0.25, a, 1, 1, g, 1, 0.5, d, 1, 0.5, e, 1, 0.5, g, 1, 0.5, d, 1, 0.5, e, 1, 1, e, 1, 1, d, 1, 1, c, 1, 0.25, d, 1, 1, e, 1, 1, d, 1, 1, e, 1, 1};


	// Musique 2 - Brasileirinho (Fonction de Luan)

	int melody_brasileirinho [] = {b, b, b, b, d, g, b, d, g, b, d, g, b, d, g, d, d, g, 466, d, g, 466, d, g, 466, d, g, 466, d, g, 466, d, g, b, d, g, b, d, g, b, d, b, b, b, b, 466, a, g};
	int tone_brasileirinho [] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	float temps_brasileirinho [] = {0.25, 0.25, 0.25, 0.25, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.25, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.25, 0.125, 0.125, 0.125, 0.125, 0.125, 0.25, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.15, 0.20, 0.25};

	// Musique 3 - 


/**
 * @class SOUND
 * @brief The SOUND class is used to sing the sounds with 3 parameters.
 *
 * This class reads the 3 parameters of one array and sing a song according to the note array, the duration array and the pause array in each cycle. 
 */

void Sound(int melody[], int duration[], int pause[]){ // Function to play the Melodies Array

	for (int nota = 0; nota < 24; nota++) {   // Sound is based on frequency, duration of sound with the frequency and duration after the break.
 
        int dur = duration[nota];
        tone(port, 2*melody[nota],dur);
  		//pausa depois das notas
        delay(pause[nota]);

    }

	noTone(port);

}

/**
 * @class SOUND
 * @brief The SOUND class is used to sing the sounds with 3 parameters.
 *
 * This class reads the 2 parameters of one array and sing a song according to the time (frequency) array and the number of cycles in this frequency. 
 */

void sound(int time, int repeat) {		// Function to play the Melodies Array

	for (int i = 1; i <= (repeat - 2) ; i++) {
		analogWrite(port,255);
	 	delayMicroseconds(time);
		analogWrite(port,0);
		delayMicroseconds(time);
	}

	delayMicroseconds(4*time);

}

/**
 * @class MUSIC
 * @brief The MUSIC class is used to sing the sounds with 2 parameters.
 *
 * This class automates the using of the class sound to read one array of sounds. 
 */

void music(int melody[], float temps[]){

	for (int i = 0; i< 155; i++){

		sound(int(melody[i]), (1000000*temps[i])/(melody[i]));

	}

}

/**
 * @class MUSIC
 * @brief The MUSIC class is used to sing the sounds with 3 parameters.
 *
 * This class automates the using of the class sound to read one array of sounds. 
 */

void music(int melody[], int tone[], float temps[]){



	for (int i = 0; i< 48; i++){

		sound(int(melody[i]/tone[i]), (1000000*temps[i]*0.5)/(melody[i]));

	}

}


void music (int power, int repeat) {

}

/**
 * @class NOTE
 * @brief The NOTE class is used to sing the sound according by the note declaration.
 *
 * This class uses the information of notes and the duration according by the number of divisions of one second that this note will be singed and nivel like one parameter of the harmonics that are used. 
 */

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

//music(sing);

//Sound(melody_Mario,duration_Mario,pause_Mario);

music(melody_brasileirinho,tone_brasileirinho,temps_brasileirinho);

}

