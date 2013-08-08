#Moti User Guide

##About

If I guess right, you just finished reading the [Installation guide](./INSTALL.md) and you're now ready to build your own code.


##Exemple: building a new behavior for Moti

Say we want to design a new behavior for Moti. How are we going to do that?

###1. Create a new directory

We want a place to put our code. Opent the Terminal and type:

```Bash
$ cd /path/to/moti
$ cd src/
$ mkdir moti_bhvr_happy
$ cd moti_bhvr_happy
```


###2. Create the new file for our code

In the Terminal, make sure you are in `/path/to/moti/src/moti_bhvr_happy` and then type:
	$ touch moti_bhvr_happy.ino

Make sure that the name of the `.ino` file is always the same as the directory it is in.

###3. Write your code

In your favorite text editor (like Sublime Text 2), open `moti_bhvr_happy.ino`. You can use the following example if you want:

``` C++
#include <Arduino.h>

// Include all the classes needed to beautifully develop your robot.
#include <Moti.h>
#include <Sensors.h>
#include <Led.h>
#include <Motors.h>
#include <Speakers.h>
#include <Memory.h>

// Then create instances of every classes
Moti moti;
Sensors sensors;
Led led;
Motors motors;
Speakers speakers;

void setup() {
	// Initialize moti
	moti.init();
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
```

Save your file.

###4. Create and configure the `Makefile`

Re-open your Terminal, make sure you are in `/path/to/moti/src/moti_bhvr_happy` and then type:

```Bash
$ touch Makefile
```

Now, open the `Makefile` in your favorite text editor and copy/past that:

```Makefile
### ATTENTION
### This is an example Makefile and it MUST be configured to suit your needs.

### the boardtag represents the board you're currently using. select the right one (uno, mega2560, etc.)
BOARD_TAG         = uno

### don't change this, our Serial communication are always using the 115200 baudrate
MONITOR_BAUDRATE  = 115200

### path to where you cloned the moti repository
PROJECT_DIR       = /Users/Ladislas/dev/leka/moti

### this is the path to the Arduino-Makefile directory.
ARDMK_DIR         = $(PROJECT_DIR)/arduino-makefile

### path to the Arduino.app directory.
### or linux, use something like:
### ARDUINO_DIR   = /usr/share/arduino
ARDUINO_DIR       = /Applications/Arduino.app/Contents/Resources/Java

### path to avr-gcc and co.
### for linux, just use:
### AVR_TOOLS_DIR = /usr
### because it adds the rest (like "/bin")
AVR_TOOLS_DIR     = /usr/local

### your path to avrdude. if you used homebrew, it should be something like that
AVRDDUDE          = /usr/local/bin/avrdude

### connect your arduino, open the IDE and look for the port
MONITOR_PORT      = /dev/tty.usbmodemfa131

### don't touch this
CURRENT_DIR       = $(shell basename $(CURDIR))

### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
include $(ARDMK_DIR)/arduino-mk/Arduino.mk
```

On OS X, you need to change: `BOARD_TAG`, `PROJECT_DIR` and `MONITOR_PORT`.

###5. Compile and upload

In your Terminal, type `make` to compile your code. It will create in directory called `bin` in `moti`.

To upload, type `make upload`.

###6. Enjoy your robot!

You can now play with your robot.
