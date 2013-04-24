//######################################################################//
//	BEWARE, EVERY NEW PCB MUST FIRST BE LOADED WITH THE ADAPTED			//
//	BOOTLOADER. IF NOT, THERE IS A HIGH RISK OF BAD FUSE CONFIGURATION!	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include <ADXL335.h>
#include <Wire.h>


//#####################//
// CONSTANT DEFINITION //
//#####################//

const int SLEEP_DELAY = 600; //	Time to elapse before the robot goes to sleep
const int AWAKE_THRESHOLD = 0; //	DO NOT USE A VALUE HIGHER THAN 150 - This threshold is used to wake up the card. The higher, the harder it is to wake up.
const int LED_MAX_BRIGHTNESS = 255;   //	Maximum led brightness
const int BLUE_LED_MAX = 255;	//	Maximum blue led brightness - it appears that the blue color is stronger than the two others
const int DELTA_ACCELERO_THRESHOLD = 2;   //	Threshold used to know is the accelerometer has moved between 2 cycles
const int GLOBAL_DELAY = 150;   //	Delay used at the end of void loop() - The higher, the slower the robot is.
const int CRAZY_ACTIVITY_THRESHOLD= 4;    //	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement. 


//################//
// PINS ASSIGMENT //
//################//

//	MOTORS - set speed and direction pins for each motor
const int MOTOR_1_SPEED = 5;
const int MOTOR_1_DIR = 4;
const int MOTOR_2_SPEED = 6;
const int MOTOR_2_DIR = 7;

//	ACCELEROMETER
const int X_PIN = A0;
const int Y_PIN = A1;
const int Z_PIN = A2;
const float Vin = 3.3;	//	Vin connected to +3.3V
ADXL335 accel(X_PIN, Y_PIN, Z_PIN, Vin);	//	constructs an instance named "accel" of the ADXL335 class

//	ICSP COMMUNICATION (used for the ADXL345, NOT ADXL335. Kept in case)
const int DATAOUT = 16; //	MOSI
const int DATAIN  = 14; //	MISO 
const int SPICLOCK  = 15; //	sck
const int SLAVESELECT = 8; //	ss

//	LED
const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;

//	MICROPHONE
const int MIC_PIN = A3;

// OTHERS

boolean isRemoteCtrl;

//###########//
// VARIABLES //
//###########//

//	GENERAL
int i;
int mic, last_Mic;
int RGB[3], RGB_BUFFER[3], fadeValue;
int MOTOR[2], MOTOR_BUFFER[2];
int XYZ[3], lastXYZ[3], deltaXYZ[3];
int sleepy;

//	DEBUG
int DEBUGSON = false;	//	make true if you need to output the sound in serial


//#######//
// SETUP //
//#######//

void setup() {

	isRemoteCtrl = false;

	MOTOR[0]=0;
	MOTOR[1]=0;
	MOTOR_BUFFER[0]=0;
	MOTOR_BUFFER[1]=0;

	//	SET PINS AS INPOUT OR OUTPUT
	pinMode(MOTOR_2_DIR, OUTPUT);
	pinMode(MOTOR_1_DIR, OUTPUT);
	pinMode(MOTOR_2_SPEED, OUTPUT);
	pinMode(MOTOR_1_SPEED, OUTPUT);

	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);

	pinMode(DATAOUT, OUTPUT);
	pinMode(DATAIN, INPUT);
	pinMode(SPICLOCK, OUTPUT);
	pinMode(SLAVESELECT, OUTPUT);

	//	SET PINS VALUE AT ZERO - 0 is the same as LOW and 1 the same as HIGH
	digitalWrite(MOTOR_2_DIR, 0);
	digitalWrite(MOTOR_1_DIR, 0);
	digitalWrite(MOTOR_2_SPEED, 0);
	digitalWrite(MOTOR_1_SPEED, 0);

	digitalWrite(RED_PIN, 0);
	digitalWrite(GREEN_PIN, 0);
	digitalWrite(BLUE_PIN, 0);

	Serial.begin(115200);

	delay(3);

	accel.update();
	lastXYZ[0] = 0;

	analogWrite(RED_PIN,50);

	Serial.println(F("Time to slowly wake up"));

	for(fadeValue = 0 ; fadeValue < BLUE_LED_MAX; fadeValue +=3) {
		analogWrite(RED_PIN, fadeValue);  
		delay(10);                            
	} 

	Serial.println(F("Let's start living!"));

	blinkLed(4);	//	Flashes the LED 4 times

	RGB[0] = 0;
	RGB[1] = 0;
	RGB[2] = BLUE_LED_MAX;

}	//	end of void setup()


//######//
// LOOP //
//######//

void loop() {

	//	Check sensors values
	mic = analogRead(MIC_PIN);
	accel.update();
	XYZ[0] = accel.getX();
	XYZ[1] = accel.getY();
	XYZ[2] = accel.getZ();

	if(isRemoteCtrl) {

		// Code for the R-Pi to take control over the PCB

	}
	else {

		if(DEBUGSON) {
			Serial.println(mic);
		}

		if (lastXYZ[0] == XYZ[0]) {
			sleepy++;
		}

		int DeltaSignal = XYZ[0] - lastXYZ[0];

		if (abs(DeltaSignal) < DELTA_ACCELERO_THRESHOLD ) 
		{
		//Serial.print(F("So small movement -Sleep"));
		// Serial.println(sleepy);
		sleepy++;
		RGB[0]-=5;  // moins rouge
		RGB[1]-=10;
		RGB[2]+=5;   //plus bleu


		MOTOR[0]-=10;
		MOTOR[1]-=10;


		}
	else
	{

	if (abs(DeltaSignal) > CRAZY_ACTIVITY_THRESHOLD) 
	{
	// Serial.print(F("So crazy movement - Mad"));
	// Serial.println(sleepy);
	sleepy=0;
	RGB[0]+=30;  // moins rouge
	RGB[1]-=10;    // pas de changement du vert
	RGB[2]-=30;   //plus bleu
	}



	}

	// Déclencher roulement si le robot est exité
	if (sleepy < 400)
	{ // Si le robot etait trop au repos alors on ajoute un délai avant de le reveiller
	if(RGB[0]>(BLUE_LED_MAX-20))
	{
	MOTOR[0]+=20;
	MOTOR[1]+=20;

	}

	}

	if(sleepy > SLEEP_DELAY)
	{ // Shut down the robot !
	blinkLed(2);
	Serial.println(F("Bye bye "));
	delay(500);
	Shutdown();
	}
	/*
	if(mic < 739)
	{
	RGB[1]+=50;
	}
	*/
	if(mic > 10)
	{
	RGB[1]+=50;
	}






	Serial.print(F(" RGB : "));
	Serial.print(RGB[0]);
	Serial.print(F(" - "));
	Serial.print(RGB[1]);
	Serial.print(F(" - "));

	Serial.print(RGB[2]);
	Serial.print(F(" MOTORs : "));
	Serial.print(MOTOR[0]);
	Serial.print(F(" - "));

	Serial.print(MOTOR[1]);
	Serial.print(F("  sleepy : "));
	Serial.print(sleepy);
	Serial.print(F("  AccX : "));
	Serial.print(XYZ[0]);
	Serial.print(F("  Mic : "));
	Serial.print(mic);
	Serial.println(F("."));
	}
	RGB_BUFFER[0] = constrain(RGB[0], 0, LED_MAX_BRIGHTNESS);  // evite de monter trop fort
	RGB_BUFFER[1] = constrain(RGB[1], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[2] = constrain(RGB[2], 0, LED_MAX_BRIGHTNESS);
	RGB[0] = RGB_BUFFER[0];
	RGB[1] = RGB_BUFFER[1];
	RGB[2] = RGB_BUFFER[2];
	analogWrite(GREEN_PIN, RGB_BUFFER[0]); // met à jour les led
	analogWrite(BLUE_PIN, RGB_BUFFER[1]); 
	analogWrite(RED_PIN, RGB_BUFFER[2]);

	MOTOR_BUFFER[0] = constrain(MOTOR[0], -255, 255);  
	MOTOR_BUFFER[1] = constrain(MOTOR[1], -255, 255);  
	MOTOR[0]=MOTOR_BUFFER[0];
	MOTOR[1]=MOTOR_BUFFER[1];
	if(MOTOR[0]<0)
	{ // recule
	analogWrite(MOTOR_2_DIR,MOTOR_BUFFER[0]); 
	analogWrite(MOTOR_1_DIR,0);
	}
	else
	{// avance
	analogWrite(MOTOR_2_DIR,0); 
	analogWrite(MOTOR_1_DIR,MOTOR_BUFFER[0]);
	}

	if(MOTOR[1]<0)
	{ // recule
	analogWrite(MOTOR_2_SPEED,MOTOR_BUFFER[1]); 
	analogWrite(MOTOR_1_SPEED,0);
	}
	else
	{// avance
	analogWrite(MOTOR_2_SPEED,0); 
	analogWrite(MOTOR_1_SPEED,MOTOR_BUFFER[1]);
	}




	delay(GLOBAL_DELAY);  // GLOBAL_DELAY
	last_Mic = mic;
	lastXYZ[0]=XYZ[0];

}


















// ------------------- Fonction ---------------------------------














void CheckRTC()
{



}




void PowerDown()
{
//I2C_Write(ADPS,TIMNG,0x01);
Serial.println(accel.getInterruptSource(),BIN);
}



void blinkLed(byte valuer)
{
for(int gro=0;gro<valuer;gro++)
{
digitalWrite(RED_PIN,1);
digitalWrite(GREEN_PIN,1);
digitalWrite(BLUE_PIN,1);
delay(50);
digitalWrite(RED_PIN,0);
digitalWrite(GREEN_PIN,0);
digitalWrite(BLUE_PIN,0);


delay(50);



}
}
int freeRam () {
extern int __heap_start, *__brkval; 
int v; 
return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}







void Shutdown()
{
//I2C_Write(ADPS,TIMNG,0x01);
Serial.println(accel.getInterruptSource(),BIN);
}




