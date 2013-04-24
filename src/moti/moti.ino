//######################################################################//
//	BEWARE, EVERY NEW PCB MUST FIRST BE LOADED WITH THE ADAPTED			//
//	BOOTLOADER. IF NOT, THERE IS A HIGH RISK OF BAD FUSE CONFIGURATION!	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//

#include <ADXL335.h>



//#####################//
// CONSTANT DEFINITION //
//#####################//

const int GLOBAL_DELAY = 75;   //	Delay used at the end of void loop() - The higher, the slower the robot is.
const int SLEEP_DELAY = 600; //	Time to elapse before the robot goes to sleep

const int AWAKE_THRESHOLD = 500; //	DO NOT USE A VALUE HIGHER THAN 150 - This threshold is used to wake up the card. The higher, the harder it is to wake up.
const int DELTA_ACCELERO_THRESHOLD = 100;   //	Threshold used to know is the accelerometer has moved between 2 cycles
const int CRAZY_ACTIVITY_THRESHOLD= 4;    //	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement. 

const int LED_MAX_BRIGHTNESS = 255;   //	Maximum led brightness
const int BLUE_LED_MAX = 255;	//	Maximum blue led brightness - it appears that the blue color is stronger than the two others



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

//	LED
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

//	MICROPHONE
const int MIC_PIN = A3;

// OTHERS
boolean isRemoteCtrl;
boolean isShutDown;



//###########//
// VARIABLES //
//###########//

//	GENERAL
int i;
int volume, lastVolume, volumeBaseline;
int RGB[3], RGB_BUFFER[3], fadeValue;
int MOTOR[2], MOTOR_BUFFER[2];
int XYZ[3], lastXYZ[3], deltaXYZ[3];
int sleepy;

//	DEBUG
boolean isDebugSound;	//	make true if you need to output the sound in serial



//#######//
// SETUP //
//#######//

void setup() {

	isRemoteCtrl = false;
	isDebugSound = false;
	isShutDown = false;

	MOTOR[0]=0;
	MOTOR[1]=0;
	MOTOR_BUFFER[0]=0;
	MOTOR_BUFFER[1]=0;

	//	SET PINS AS INPOUT OR OUTPUT
	setPinsAsOutput();

	//	SET PINS VALUE AT ZERO - 0 is the same as LOW and 1 the same as HIGH
	setPinsValuesToZero():

	//	Begin serial for debug
	Serial.begin(115200);

	delay(3);

	// Check the ambient noise to make is the volume baseline for the current run of the programm.
	volumeBaseline = analogRead(MIC_PIN);

	// Update the accelerometer and 
	accel.update();
	lastXYZ[0] = accel.getX() * 1000;
	lastXYZ[1] = accel.getY() * 1000;
	lastXYZ[2] = accel.getZ() * 1000;

	analogWrite(RED_PIN, 50);

	delay(100);

	Serial.println(F("Time to slowly wake up ============"));

	//	Wake up with a beautiful fade to blue
	for(fadeValue = 0 ; fadeValue < BLUE_LED_MAX; fadeValue +=3) {
		analogWrite(RED_PIN, fadeValue);  
		delay(10);                            
	} 

	Serial.println(F("Let's start living!\n"));

	blinkLed(4);

	RGB[0] = 0;
	RGB[1] = 0;
	RGB[2] = BLUE_LED_MAX;

}



//######//
// LOOP //
//######//

void loop() {

	//	Check sensors values
	volume = analogRead(MIC_PIN);
	accel.update();
	XYZ[0] = accel.getX() * 1000;
	XYZ[1] = accel.getY() * 1000;
	XYZ[2] = accel.getZ() * 1000;

	deltaXYZ[0] = XYZ[0] - lastXYZ[0];
	deltaXYZ[1] = XYZ[1] - lastXYZ[1];
	deltaXYZ[2] = XYZ[2] - lastXYZ[2];

	if(isShutDown) {
		digitalWrite(RED_PIN,1);
		digitalWrite(GREEN_PIN,0);
		digitalWrite(BLUE_PIN,0);
 
		// Code for the R-Pi to take control over the PCB
		delay(100);
 
		digitalWrite(RED_PIN,0);
		digitalWrite(GREEN_PIN,1);
		digitalWrite(BLUE_PIN,0);
 
		delay(100);
 
		digitalWrite(RED_PIN,0);
		digitalWrite(GREEN_PIN,0);
		digitalWrite(BLUE_PIN,1);

		delay(100);

		if ( abs(deltaXYZ[0]) > AWAKE_THRESHOLD || abs(deltaXYZ[1]) > AWAKE_THRESHOLD || abs(deltaXYZ[2]) > AWAKE_THRESHOLD) {
			softwareReset();
		}
	}
	else {

		if(isDebugSound) {
			Serial.println(volume);
		}

		if (lastXYZ[0] == XYZ[0]) {
			sleepy++;
		}

		if (abs(deltaXYZ[0]) < DELTA_ACCELERO_THRESHOLD) {
			sleepy++;

			RGB[0]-=5;
			RGB[1]-=10;
			RGB[2]+=5;

			MOTOR[0]-=10;
			MOTOR[1]-=10;
		}
		else {
			if (abs(deltaXYZ[0]) > CRAZY_ACTIVITY_THRESHOLD) {
				sleepy=0;
				RGB[0]+=30;
				RGB[1]-=10;
				RGB[2]-=30;
			}
		}

		if (sleepy < 400) {
			if(RGB[0]>(BLUE_LED_MAX-20)) {
				MOTOR[0]+=20;
				MOTOR[1]+=20;
			}
		}

		if(sleepy > SLEEP_DELAY) {
			blinkLed(2);
			Serial.println(F("It's time to go to sleep!"));
			delay(500);
			shutDown();
		}

		if(volume > volumeBaseline) {
			RGB[1]+=50;
		}
		else {
			RGB[1]-=10;
		}

	}

	// Constrain the RGB[] values between zero and LED_MAX_BRIGHTNESS
	RGB_BUFFER[0] = constrain(RGB[0], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[1] = constrain(RGB[1], 0, LED_MAX_BRIGHTNESS);
	RGB_BUFFER[2] = constrain(RGB[2], 0, LED_MAX_BRIGHTNESS);

	// Set RGB[] to the buffer values
	RGB[0] = RGB_BUFFER[0];
	RGB[1] = RGB_BUFFER[1];
	RGB[2] = RGB_BUFFER[2];

	// Output the values
	analogWrite(RED_PIN, RGB_BUFFER[0]);
	analogWrite(GREEN_PIN, RGB_BUFFER[1]); 
	analogWrite(BLUE_PIN, RGB_BUFFER[2]);

	MOTOR_BUFFER[0] = constrain(MOTOR[0], -255, 255);  
	MOTOR_BUFFER[1] = constrain(MOTOR[1], -255, 255);

	MOTOR[0]=MOTOR_BUFFER[0];
	MOTOR[1]=MOTOR_BUFFER[1];

	if(MOTOR[0] > 0) {	// Go forward
		digitalWrite(MOTOR_1_DIR, 1);
		analogWrite(MOTOR_1_SPEED, 	abs(MOTOR[0]));
	}
	else {	//	Go backward
		digitalWrite(MOTOR_1_DIR, 0);
		analogWrite(MOTOR_1_SPEED, 	abs(MOTOR[0]));
	}

	if(MOTOR[1] > 0) { // Go forward
		digitalWrite(MOTOR_2_DIR, 1);
		analogWrite(MOTOR_2_SPEED, 	abs(MOTOR[1]));
	}
	else {	//	Go backward
		digitalWrite(MOTOR_2_DIR, 0);
		analogWrite(MOTOR_2_SPEED, 	abs(MOTOR[1]));
	}

	lastVolume = volume;
	lastXYZ[0]=XYZ[0];
	lastXYZ[1]=XYZ[1];
	lastXYZ[2]=XYZ[2];

	sendSerialFeedback();

	delay(GLOBAL_DELAY);

}