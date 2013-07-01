
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

int value1, value2, value3;

//#######//
// SETUP //
//#######//

void setup() {
	Moti.initVerbose();
}



//######//
// LOOP //
//######//

void loop() {
	Serial.println();

	Serial.println(F("Starting Loop"));
	delay(1000);


	////////////	CHECKING INITIALIZATION 	////////////

	Serial.println();

	Serial.println(F("Checking if the initialization was done correctly"));
	Serial.println(F("using getRgbValue(int index)"));

	Serial.println();

	Serial.print(F("\tgetRgbValue(0) = "));
	Serial.println(Moti.getRgbValue(0));
	delay(500);
	Serial.print(F("\tgetRgbValue(1) = "));
	Serial.println(Moti.getRgbValue(1));
	delay(500);
	Serial.print(F("\tgetRgbValue(2) = "));
	Serial.println(Moti.getRgbValue(2));
	delay(500);

	Serial.println();

	Serial.println(F("Checking if the initialization was done correctly"));
	Serial.println(F("using getRed/Green/Blue()"));

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);
	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);
	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.initializeLed();
	delay(500);


	////////////	CHECKING SETTING VALUES 	////////////

	Serial.println();

	Serial.println(F("Checking if setting is done correctly"));
	Serial.println(F("using setRgbValue(uint8_t index, int value)"));
	delay(500);

	Serial.println();

	Serial.print(F("\tsetRgbValue(0, "));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setRgbValue(0, value1);
	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tsetRgbValue(1, "));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setRgbValue(1, value1);
	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tsetRgbValue(2, "));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setRgbValue(2, value1);
	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.initializeLed();
	delay(500);


	////////////	CHECKING PRINTING COLORS 	////////////

	Serial.println();
	Serial.println(F("Checking if printing is done correctly"));
	Serial.println(F("using printRgbColor()"));
	delay(500);

	Serial.print(F("\tsetRed("));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setRed(value1);
	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tsetGreen("));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setGreen(value1);
	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tsetBlue("));
	value1 = random(-500, 500);
	Serial.print(value1);
	Serial.println(F(")"));
	Moti.setBlue(value1);
	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.printRgbColor();

	Moti.initializeLed();
	delay(500);

	Serial.println();
	Serial.println(F("Checking if printing is done correctly"));
	Serial.println(F("using printRgbColor(int redValue, int greenValue, int blueValue)"));
	delay(500);

	Serial.println();

	value1 = random(-500,500);
	value2 = random(-500,500);
	value3 = random(-500,500);

	Serial.print(F("\tprintRgbColor("));
	Serial.print(value1);
	Serial.print(F(", "));
	Serial.print(value2);
	Serial.print(F(", "));
	Serial.print(value3);
	Serial.print(F(");"));

	Moti.printRgbColor(value1, value2, value3);

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.initializeLed();
	delay(500);

	Serial.println();
	Serial.println(F("Checking if printing is done correctly"));
	Serial.println(F("using printRgbColor(String colorName)"));
	delay(500);

	Serial.println();

	Serial.print(F("\tprintRgbColor(\"red\")"));

	Moti.printRgbColor("red");

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Serial.print(F("\tprintRgbColor(\"light green\")"));

	Moti.printRgbColor("light green");

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Serial.print(F("\tprintRgbColor(\"rand\")"));

	Moti.printRgbColor("rand");

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.initializeLed();
	delay(500);

	Serial.println();
	Serial.println(F("Checking if printing is done correctly"));
	Serial.println(F("using fadeLedTo(String colorName)"));
	delay(500);

	Serial.println();

	Serial.print(F("\tfadeLedTo(\"red\")"));

	Moti.fadeLedTo("red");

	Serial.println();

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Serial.print(F("\tfadeLedTo(\"light green\")"));

	Moti.fadeLedTo("light green");

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Serial.print(F("\tfadeLedTo(\"rand\")"));

	Moti.fadeLedTo("rand");

	Serial.print(F("\tgetRed() = "));
	Serial.println(Moti.getRed());
	delay(500);

	Serial.print(F("\tgetGreen() = "));
	Serial.println(Moti.getGreen());
	delay(500);

	Serial.print(F("\tgetBlue() = "));
	Serial.println(Moti.getBlue());
	delay(500);

	Moti.initializeLed();
	delay(500);

	Serial.println();
	Serial.println(F("Ending Loop"));
	delay(1000);

	delay(4000);
}