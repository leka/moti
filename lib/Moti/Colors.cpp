#ifndef __ROBOT_LEKA_ARDUINO_COLORS_H_
#define __ROBOT_LEKA_ARDUINO_COLORS_H_

#include "Arduino.h"
#include "Moti.h"

class Colors {

	public:

		Colors();

		void initialize();

		void addColor(char* colorName, int red, int green, int blue);

		void getRedFrom(char* colorName);
		void getGreenFrom(char* colorName);
		void getBlueFrom(char* colorName);

	private:

		char* colorName;
		int red;
		int green;
		int blue;


};

#endif