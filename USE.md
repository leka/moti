#Moti User Guide

##About

If I guess right, you just finished reading the [Installation guide](./INSTALL.md) and you're now ready to build your own code.


##Exemple: building a new behavior for Moti

Say we want to design a new behavior for Moti. How are we going to do that?

###1. Create a new directory

We want a place to put our code. Opent the Terminal and type:

	$ cd /path/to/moti
	$ cd src/
	$ mkdir moti_bhvr_happy
	$ cd moti_bhvr_happy


###2. Create the new file for our code

In the Terminal, make sure you are in `/path/to/moti/src/moti_bhvr_happy` and then type:
	$ touch moti_bhvr_happy.ino

Make sure that the name of the `.ino` file is always the same as the directory it is in.

###3. Write your code

In your favorite text editor (like Sublime Text 2), open `moti_bhvr_happy.ino`. You can use the following example if you want:

	#include "Arduino.h"
	#include "Moti.h"

	MOTI Moti = MOTI();

	void setup() {
		Moti.init();
	}

	void loop() {
		Moti.goForward();
		delay(5000);
		Moti.blinkLed(4);
		delay(2000);
		Moti.spinRight();
		delay(2000);
		Moti.stop();
		delay(2000);
		Moti.blinkLed(10);
		delay(1000);
	}

Save your file.

###4. Create and configure the `Makefile`

Re-open your Terminal, make sure you are in `/path/to/moti/src/moti_bhvr_happy` and then type:

	$ touch Makefile

Now, open the `Makefile` in your favorite text editor and copy/past that:

	BOARD_TAG     = uno

	ARDMK_DIR     = ~/dev/arduino/arduino-makefile

	ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java

	AVR_TOOLS_DIR = /usr/local

	ARDUINO_PORT  = /dev/tty.usbmodemfa131

	PROJECT_DIR = /path/to/moti

	CURRENT_DIR = $(shell basename $(CURDIR))

	include /path/to/arduino-makefile/arduino-mk/Arduino.mk

You need to change: `BOARD_TAG`, `ARDMK_DIR`, `RDUINO_PORT`, `PROJECT_DIR`, `include /...`

###5. Compile and upload

In your Terminal, type `make` to compile your code. It will create in directory called `bin` in `moti`.

To upload, type `make upload`.

###6. Enjoy your robot!

You can now play with your robot.
