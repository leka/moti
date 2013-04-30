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
const int DELTA_ACCELERO_THRESHOLD = 200;   //	Threshold used to know is the accelerometer has moved between 2 cycles
const int CRAZY_ACTIVITY_THRESHOLD= 4;    //	Is used to know if the activity around the robot is important. If so, the robot gets excited much faster - Smaller value means more excitement. 

const int LED_MAX_BRIGHTNESS = 255;   //	Maximum led brightness
const int BLUE_LED_MAX = 200;	//	Maximum blue led brightness - it appears that the blue color is stronger than the two others

const int DELTA_VOLUME_THRESHOLD = 4;



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



//###########//
// VARIABLES //
//###########//

//	GENERAL
int i;
int volume, lastVolume, deltaVolume, volumeBaseline;
int RGB[3], RGB_BUFFER[3], fadeValue;
int MOTOR[2], MOTOR_BUFFER[2];
int XYZ[3], lastXYZ[3], deltaXYZ[3];
int sleepy;

//	DEBUG
boolean isDebugSound;	//	make true if you need to output the sound in serial
boolean isRemoteCtrl;
boolean isShutDown;


//#######//
// SETUP //
//#######//

void setup() {

	isRemoteCtrl = false;
	isDebugSound = false;
	isShutDown = false;

	setRgbAndMotorToZero();

	//	SET PINS AS INPOUT OR OUTPUT
	setPinsAsOutput();

	//	SET PINS VALUE AT ZERO - 0 is the same as LOW and 1 the same as HIGH
	setPinsValuesToZero();

	//	Begin serial for debug
	Serial.begin(9600);

	delay(3);

	// Check the ambient noise to make is the volume baseline for the current run of the programm.
	volumeBaseline = analogRead(MIC_PIN);
	lastVolume = volumeBaseline;

	// Update the accelerometer and get the xyz values
	accel.update();
	lastXYZ[0] = accel.getX() * 1000;	//	we need to multiply by 1000 to have the decimals. we don't want to use float because it requires more resources to compute.
	lastXYZ[1] = accel.getY() * 1000;
	lastXYZ[2] = accel.getZ() * 1000;

	Serial.println(F("Time to slowly wake up ============"));

	//	Wake up with a beautiful fade to blue
	fadeToBlue();

	Serial.println(F("Let's start living!\n"));

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

	lastVolume = volume;
	lastXYZ[0] = XYZ[0];
	lastXYZ[1] = XYZ[1];
	lastXYZ[2] = XYZ[2];

	delay(GLOBAL_DELAY);
}
