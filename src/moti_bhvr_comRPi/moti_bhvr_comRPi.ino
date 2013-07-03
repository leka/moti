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


MOTI Moti = MOTI();



int X_VALUE, Y_VALUE, Z_VALUE, YAW_VALUE, PITCH_VALUE, ROLL_VALUE;

void sendBinaryInt(int value)
{
  // send the two bytes that comprise a two byte (16 bit) integer
  // Serial.println("Data");
  // Serial.write(lowByte(value));  // send the low byte
  // Serial.write(highByte(value)); // send the high byte

  Serial.println(lowByte(value));  // send the low byte
  Serial.println(highByte(value));
}

void sendBinaryByte(byte value)
{
  Serial.write(value);
}

//#######//
// SETUP //
//#######//

void setup() {
	Moti.init();

	delay(500);

	sendBinaryByte(INIT_PHASE);
}

//######//
// LOOP //
//######//

void loop() {

	Moti.checkSensors();

	if(Serial.available() > 0){

		int incomingByte = Serial.read();

		sendBinaryByte(ANSWER_START);

		sendBinaryByte(NBR_DATA);

		sendBinaryByte(ACC_TYPE);

		sendBinaryInt(0x06);
		Serial.println("Bin Acc");
		sendBinaryInt(Moti.getXYZ(0));
		sendBinaryInt(Moti.getXYZ(1));
		sendBinaryInt(Moti.getXYZ(2));

		sendBinaryByte(GYR_TYPE);

		sendBinaryInt(0x06);

		int yaw = (int) Moti.getYPR(0);
		int pitch =(int) Moti.getYPR(1);
		int roll = (int) Moti.getYPR(2);
Serial.println("Bin Gyr");
		sendBinaryInt(yaw);
		sendBinaryInt(pitch);
		sendBinaryInt(roll);

		// Serial.println((int) Moti.getYPR(0));
		// Serial.println((int) Moti.getYPR(1));
		// Serial.println((int) Moti.getYPR(2));
		sendBinaryByte(ANSWER_END);
	}
}


