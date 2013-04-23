//######################################################################//
//	BEWARE, EVERY NEW PCB MUST FIRST BE LOADED WITH THE ADAPTED					//
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

const int SLEEP_DELAY = 600; // delay to elapse before the robot goes to sleep
const int AWAKE_THRESHOLD = 0; // valeur 0 < 250; seuil de reveil de la carte Eteint -> Reveil
const int LED_MAX_BRIGHTNESS = 200;   // seuil max d'éclairage des led
const int BLUE_LED_MAX = 180;  
const int DELTA_SIGNAL_INACTIVATION = 2;   // seuil min pour detection inact
const int GLOBAL_DELAY = 150;   // ralentir ou rendre plus rapide le robot, plus c'est grand moins il se calme vite
const int CRAZY_ACTIVITY = 4;    // Diminuer pour que le robot s'exsite plus vite ! 


//################//
// PINS ASSIGMENT //
//################//

//	MOTORS
const int mot_IN4 = 4;
const int mot_IN2 = 5;
const int mot_IN3 = 6;
const int mot_IN1 = 7;

//	ACCELEROMETER
const int X_PIN = A0;
const int Y_PIN = A1;
const int Z_PIN = A2;
const float Vin = 3.3;	//	Vin connected to +3.3V
ADXL335 accel(X_PIN, Y_PIN, pin_z, Vin);	//	constructs an instance of the ADXL335 class

//	ICSP COMMUNICATION
const int DATAOUT = 16; //	MOSI
const int DATAIN  = 14; //	MISO 
const int SPICLOCK  = 15; //	sck
const int SLAVESELECT = 8; //	ss

//	LED
const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;

//	MICROPHONE
const int MIC_PIN = 3; //analog

//###########//
// VARIABLES //
//###########//

//	GENERAL
int i, mic, XYZ[3], RGB[3], RGB_BUFFER[3], MOTOR[2], MOTOR_BUFFER[2];
int last_XYZ, last_Mic;
int Sleepy;

//	DEBUG
int DEBUGSON = false;	//	make true if you need to output the sound in serial


// ----------------------------------------------------------------------
// ----------------------- SETUP ----------------------------------------
// ----------------------------------------------------------------------
void setup() {

REMOTE_CTRL= false;

MOTOR[0]=0;
MOTOR[1]=0;
MOTOR_BUFFER[0]=0;
MOTOR_BUFFER[1]=0;

/* Initialize pinout */
pinMode(mot_IN1, OUTPUT);
pinMode(mot_IN2, OUTPUT);
pinMode(mot_IN3, OUTPUT);
pinMode(mot_IN4, OUTPUT);
pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);
pinMode(DATAOUT, OUTPUT);
pinMode(DATAIN, INPUT);
pinMode(SPICLOCK, OUTPUT);
pinMode(SLAVESELECT, OUTPUT);

digitalWrite(mot_IN1,0);
digitalWrite(mot_IN2,0);
digitalWrite(mot_IN3,0);
digitalWrite(mot_IN4,0);
digitalWrite(RED_PIN,0);
digitalWrite(GREEN_PIN,0);
digitalWrite(BLUE_PIN,0);
Serial.begin(115200);

delay(3);

CheckAccelero();
accel.readAccel(XYZ);

analogWrite(RED_PIN,50);



// Allumage led bleu : Reveil du robot en douceur avec un jolie fade 

Serial.println(F("Reveil douceur"));
for(int fadeValue = 0 ; fadeValue < BLUE_LED_MAX; fadeValue +=3) { 
// sets the value (range from 0 to 255):
analogWrite(RED_PIN, fadeValue);  
delay(10);                            
} 

Serial.println(F("Debut comportement"));

Blinki(4);  // On excite un peu la boule en flashant les led à fond !

RGB[0] = 0;  // moins rouge
RGB[1] = 0;   // pas de changement du vert
RGB[2] = BLUE_LED_MAX;   //plus bleu

}



// -------------- MAIN ------ -----------------//
void loop() {



// relevé des capteurs
mic = analogRead(MIC_PIN);   // micro
accel.readAccel(XYZ);          // accelerometre

if(REMOTE_CTRL == true)
{
// partie concernant la commande du robot par la Raspberry PI (RPI)





}
else
{

if(DEBUGSON)
{

Serial.println(mic);
}


// On check les variations des capteurs

if (last_XYZ == XYZ[0])
{ // pas du tout de mouvement sur axe X
// Serial.print(F("No Accel activity-Sleep"));
// Serial.println(Sleepy);
Sleepy++;
}

int DeltaSignal = XYZ[0] - last_XYZ;
if (abs(DeltaSignal) < DELTA_SIGNAL_INACTIVATION ) 
{
//Serial.print(F("So small movement -Sleep"));
// Serial.println(Sleepy);
Sleepy++;
RGB[0]-=5;  // moins rouge
RGB[1]-=10;
RGB[2]+=5;   //plus bleu


MOTOR[0]-=10;
MOTOR[1]-=10;


}
else
{

if (abs(DeltaSignal) > CRAZY_ACTIVITY ) 
{
// Serial.print(F("So crazy movement - Mad"));
// Serial.println(Sleepy);
Sleepy=0;
RGB[0]+=30;  // moins rouge
RGB[1]-=10;    // pas de changement du vert
RGB[2]-=30;   //plus bleu
}



}

// Déclencher roulement si le robot est exité
if (Sleepy < 400)
{ // Si le robot etait trop au repos alors on ajoute un délai avant de le reveiller
if(RGB[0]>(BLUE_LED_MAX-20))
{
MOTOR[0]+=20;
MOTOR[1]+=20;

}

}

if(Sleepy > SLEEP_DELAY)
{ // Shut down the robot !
Blinki(2);
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
Serial.print(F("  Sleepy : "));
Serial.print(Sleepy);
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
analogWrite(mot_IN1,MOTOR_BUFFER[0]); 
analogWrite(mot_IN2,0);
}
else
{// avance
analogWrite(mot_IN1,0); 
analogWrite(mot_IN2,MOTOR_BUFFER[0]);
}

if(MOTOR[1]<0)
{ // recule
analogWrite(mot_IN3,MOTOR_BUFFER[1]); 
analogWrite(mot_IN4,0);
}
else
{// avance
analogWrite(mot_IN3,0); 
analogWrite(mot_IN4,MOTOR_BUFFER[1]);
}




delay(GLOBAL_DELAY);  // GLOBAL_DELAY
last_Mic = mic;
last_XYZ=XYZ[0];

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



void Blinki(byte valuer)
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




