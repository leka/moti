//######################################################################//
//	MOTI SOFTWARE v1.0													//
//	COPYRIGHT WE ARE LEKA! - SOURCE CODE DISTRIBUTED UNDER MIT LICENCE	//
//######################################################################//


//###########//
// LIBRARIES //
//###########//
#include <RGBLED.h>

#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>

#define DEBUG
#ifdef DEBUG
#include <DebugUtils.h>
#endif

#include <CommunicationUtils.h>
#include <FreeSixIMU.h>
#include <Wire.h>



//#####################//
// CONSTANT DEFINITION //
//#####################//

const int GLOBAL_DELAY = 75;   //	Delay used at the end of void loop() - The higher, the slower the robot is.
const int SLEEP_DELAY = 600; //	Time to elapse before the robot goes to sleep

const int AWAKE_THRESHOLD = 500; //	DO NOT USE A VALUE HIGHER THAN 150 - This threshold is used to wake up the card. The higher, the harder it is to wake up.
const int DELTA_ACCELERO_THRESHOLD = 200;   //	Threshold used to know if the accelerometer has moved between 2 cycles
const int CRAZY_ACTIVITY_THRESHOLD= 10;    //	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement.

const int LED_MAX_BRIGHTNESS = 255;	//	Maximum led brightness
const int RED_MAX_BRIGHTNESS = 255;
const int GREEN_MAX_BRIGHTNESS = 255;
const int BLUE_LED_MAX = 255;	//	Maximum blue led brightness - it appears that the blue color is stronger than the two others



//##############################################//
// ACCELEROMETER, GYROSCOPE AND RGB LED CLASSES //
//##############################################//

//	ACCELEROMETER
FreeSixIMU AccelGyro = FreeSixIMU();

//	LED
RGBLED RGBLED = RGBLED(9,10,11);



//######################//
// MOTOR PINS ASSIGMENT //
//######################//

//	MOTORS - set speed and direction pins for each motor
const int MOTOR_1_SPEED = 5;
const int MOTOR_1_DIR = 4;
const int MOTOR_2_SPEED = 6;
const int MOTOR_2_DIR = 7;



//###########//
// VARIABLES //
//###########//

//	GENERAL
int i;
int RGB[3], RGB_BUFFER[3];
int MOTOR[2], MOTOR_BUFFER[2];
int XYZ[3], lastXYZ[3], deltaXYZ[3];
int sleepy;

//	DEBUG
boolean isRemoteCtrl;
boolean isShutDown;


//#######//
// SETUP //
//#######//

void setup() {

	//	Begin serial connection using XBEE
	Serial.begin(115200);
	Serial.println(F("Moti is waking up."));
	println();


	//	Slowly fade LED to blue
	fadeToBlue();

	delay(100);


	//	Starting Wire
	Serial.println(F("Wire begin."));

		Wire.begin();

	delay(100);
	Serial.println(F("Wire OK."));
	println();

	delay(100);`


	// Accelerometer and gyroscope initialization
	Serial.println(F("Accelerometer and gyroscope initialization."));

		AccelGyro.init();

	delay(100);
	Serial.println(F("Accelerometer and gyroscope OK."));
	println();


	// Set isRemoteCtrl and isShutdown to false
	Serial.println(F("Setting up isRemoteCtrl and isShutDown to FALSE."));

		isRemoteCtrl = false;
		isShutDown = false;

	delay(100);
	Serial.println(F("isRemoteCtrl and isShutDown OK."));
	println();

	// Set pins as output for the motors
	Serial.println(F("Setting Motor pins as OUTPUT."));

		setPinsAsOutput();
		setPinsValuesToZero();

	delay(100);
	Serial.println(F("Pins as OUTPUT OK."));
	println();

	delay(100);

	println(F("Everything is up and running, let's hack autism!"));

	blinkLed(4);
}



//######//
// LOOP //
//######//

void loop() {

	//	Check sensors values
	checkSensors();

	if(isShutDown) {
		setPinsValuesToZero();
		setRgbAndMotorToZero();

		//sendSerialFeedback();
		sendProcessingFeedback(); // JUST COMMENT ONE OF THE TWO LINES

		if ( deltaXYZ[0] > AWAKE_THRESHOLD || deltaXYZ[1] > AWAKE_THRESHOLD || deltaXYZ[2] > AWAKE_THRESHOLD) {
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

		if (deltaXYZ[0] < DELTA_ACCELERO_THRESHOLD) {
			sleepy++;

			RGB[0]-=5;
			RGB[1]-=10;
			RGB[2]+=5;

			MOTOR[0]-=10;
			MOTOR[1]-=10;
		}
		else {
			if (deltaXYZ[0] > CRAZY_ACTIVITY_THRESHOLD) {
				sleepy=0;
				RGB[0]+=30;
				RGB[1]+=10;
				RGB[2]-=30;
			}
		}

		if(deltaVolume > DELTA_VOLUME_THRESHOLD && deltaVolume > abs(volume - volumeBaseline)) {
			RGB[1]+=50;
		}
		else {
			RGB[1]-=10;
		}

		if(sleepy > SLEEP_DELAY) {
			blinkLed(2);
			Serial.println(F("It's time to go to sleep!"));
			delay(500);
			shutDown();
		}

		setRgbLed();

		setMotorSpeedAndDirection();

		//sendSerialFeedback();
		sendProcessingFeedback(); //JUST COMMENT ONE OF THE TWO LINES
	}

	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	delay(GLOBAL_DELAY);
}
