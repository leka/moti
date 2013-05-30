void setupMoti_VERBOSE(){

	RGBLED.blinkLED(4);
	RGBLED.setToZero();
	//	Begin serial connection using XBEE
	Serial.begin(115200);
	Serial.println(F("Moti is waking up."));
	Serial.println("");


	delay(50);


	//	Starting Wire
	Serial.println(F("Wire begin."));

		Wire.begin();

	delay(50);
	Serial.println(F("Wire OK."));
	Serial.println("");

	delay(50);


	// Accelerometer and gyroscope initialization
	Serial.println(F("Accelerometer and gyroscope initialization."));

		AccelGyro.init();

	delay(50);
	Serial.println(F("Accelerometer and gyroscope OK."));
	Serial.println("");


	// Set isRemoteCtrl and isShutdown to false
	Serial.println(F("Setting up isRemoteCtrl and isShutDown to FALSE."));

		isRemoteCtrl = false;
		isShutDown = false;

	delay(50);
	Serial.println(F("isRemoteCtrl and isShutDown OK."));
	Serial.println("");

	// Set pins as output for the motors
	Serial.println(F("Setting Motor pins as OUTPUT."));

		setMotorPinAsOutput();
		setMotorPinToZero();
		setMotorValueToZero();

	delay(50);
	Serial.println(F("Pins as OUTPUT OK."));
	Serial.println("");

	delay(50);

	Serial.println(F("Everything is up and running, let's hack autism!"));

	RGBLED.fadeToBlue();
	RGBLED.blinkLED(4);
}


void setupMoti_QUIET(){

	RGBLED.blinkLED(4);
	RGBLED.setToZero();

	//	Begin serial connection using XBEE
	Serial.begin(115200);

	//	Slowly fade LED to blue

	Wire.begin();

	delay(50);

	AccelGyro.init();

	delay(50);

	isRemoteCtrl = false;
	isShutDown = false;

	delay(50);

	setMotorPinAsOutput();
	setMotorPinToZero();
	setMotorValueToZero();

	delay(50);

	RGBLED.fadeToBlue();
	RGBLED.blinkLED(4);
}