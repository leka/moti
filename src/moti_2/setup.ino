void setupMoti_VERBOSE(){
	//	Begin serial connection using XBEE
	Serial.begin(115200);
	Serial.println(F("Moti is waking up."));
	Serial.println("");


	delay(100);


	//	Starting Wire
	Serial.println(F("Wire begin."));

		Wire.begin();

	delay(100);
	Serial.println(F("Wire OK."));
	Serial.println("");

	delay(100);


	// Accelerometer and gyroscope initialization
	Serial.println(F("Accelerometer and gyroscope initialization."));

		AccelGyro.init();

	delay(100);
	Serial.println(F("Accelerometer and gyroscope OK."));
	Serial.println("");


	// Set isRemoteCtrl and isShutdown to false
	Serial.println(F("Setting up isRemoteCtrl and isShutDown to FALSE."));

		isRemoteCtrl = false;
		isShutDown = false;

	delay(100);
	Serial.println(F("isRemoteCtrl and isShutDown OK."));
	Serial.println("");

	// Set pins as output for the motors
	Serial.println(F("Setting Motor pins as OUTPUT."));

		setMotorPinAsOutput();
		setMotorPinToZero();
		setMotorValueToZero();

	delay(100);
	Serial.println(F("Pins as OUTPUT OK."));
	Serial.println("");

	delay(100);

	Serial.println(F("Everything is up and running, let's hack autism!"));

	RGBLED.fadeToBlue();
}


void setupMoti_QUIET(){
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
}