#include "Moti.h"
#include "Arduino.h"

//###########################//
// DATA TRANSFER TO COMPUTER //
//###########################//

void MOTI::sendDataToProcessing(){
	Serial.print(XYZ[0]);
	Serial.print(',');
	Serial.print(XYZ[1]);
	Serial.print(',');
	Serial.print(XYZ[2]);

	Serial.print(',');

	Serial.print(deltaXYZ[0]);
	Serial.print(',');
	Serial.print(deltaXYZ[1]);
	Serial.print(',');
	Serial.print(deltaXYZ[2]);

	Serial.print(',');

	Serial.print(rgb[0]);
	Serial.print(',');
	Serial.print(rgb[1]);
	Serial.print(',');
	Serial.print(rgb[2]);

	Serial.print(',');
	// Serial.print(rightMotor);
	Serial.print(',');
	// Serial.println(leftMotor);
}

void MOTI::sendDataToDebug(){
	Serial.print(F("Sleep: "));
	Serial.print(sleepy);

	Serial.print(F("R: "));
	Serial.print(rgb[0]);
	Serial.print(F(" G: "));
	Serial.print(rgb[1]);
	Serial.print(F(" B: "));
	Serial.print(rgb[2]);

	Serial.print(F(" | MOTOR 1: "));
	// Serial.print(rightMotor);
	Serial.print(F(" MOTOR 2: "));
	// Serial.print(leftMotor);

	Serial.print(F(" | X: "));
	Serial.print(XYZ[0]);
	Serial.print(F(" Y: "));
	Serial.print(XYZ[1]);
	Serial.print(F(" Z: "));
	Serial.print(XYZ[2]);

	Serial.print(F(" | dX: "));
	Serial.print(deltaXYZ[0]);
	Serial.print(F(" dY: "));
	Serial.print(deltaXYZ[1]);
	Serial.print(F(" dZ: "));
	Serial.println(deltaXYZ[2]);
}

void MOTI::sendDataJson(){
	Serial.print(F("{"));
		Serial.print(F("\" accel\" : "));
			Serial.print(F("{"));

				Serial.print(F(" \"x\" : "));
				Serial.print(XYZ[0]);
				Serial.print(F(","));

				Serial.print(F(" \"y\" : "));
				Serial.print(XYZ[1]);
				Serial.print(F(","));

				Serial.print(F(" \"z\" : "));
				Serial.print(XYZ[2]);

			Serial.print(F(" },"));

		Serial.print(F("\" gyro\" : "));
			Serial.print(F("{"));

				Serial.print(F(" \"yaw\" : "));
				Serial.print(YPR[0]);
				Serial.print(F(","));

				Serial.print(F(" \"pitch\" : "));
				Serial.print(YPR[1]);
				Serial.print(F(","));

				Serial.print(F(" \"roll\" : "));
				Serial.print(YPR[2]);

			Serial.print(F(" },"));

		Serial.print(F("\" rgb\" : "));
			Serial.print(F("{"));

				Serial.print(F(" \"red\" : "));
				Serial.print(rgb[0]);
				Serial.print(F(","));

				Serial.print(F(" \"green\" : "));
				Serial.print(rgb[1]);
				Serial.print(F(","));

				Serial.print(F(" \"blue\" : "));
				Serial.print(rgb[2]);

			Serial.print(F(" }"));
	Serial.println(F("}"));
}
