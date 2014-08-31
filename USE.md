# Developing behaviors for Moti

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Introduction](#introduction)
- [Overview of the API](#overview-of-the-api)
  - [`Motion`](#motion)
  - [`Light`](#light)
  - [`Moti`](#moti)
  - [`Monitor`](#monitor)
- [Anatomy of a program](#anatomy-of-a-program)
  - [Directory structure](#directory-structure)
  - [Threads and procedures](#threads-and-procedures)
    - [The `start()` procedure](#the-start-procedure)
    - [The `run()` procedure](#the-run-procedure)
    - [The `stop()` procedure](#the-stop-procedure)
    - [The `thread` procedure](#the-thread-procedure)
- [Building a basic example](#building-a-basic-example)
  - [Introduction](#introduction-1)
  - [Stabilization?!](#stabilization!)
  - [Let's code!](#lets-code!)
    - [Creating the files and the directories](#creating-the-files-and-the-directories)
    - [The `Stabilization` behavior](#the-stabilization-behavior)
    - [The `main thread`](#the-main-thread)
- [Go further, multiple behaviors](#go-further-multiple-behaviors)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introduction

Moti is a spherical robotic smart toy, specially designed to help exceptional children, such as children with *Autism Spectrum Disorders*.

The code that runs on Moti is **open source**, which means that you are welcome to contribute to the project and help improve existing behaviors or create new ones.

In this tutorial, you'll learn how to develop your own program for Moti.

But before, let's take a brief look at the API.

## Overview of the API

The API has been developed to be...

*	easy to use
*	robust
*	and wide enough to let you do whatever you'd like to do

This is just an overview, for further information, Doxygen generated documentation is available [here](#).

### `Motion`

The `Motion` API lets you control Moti's motion.

The `Motion` API runs in its own `thread` and is `non-blocking`: while moving, Moti can still perform other actions such as blinking a led or checking if it is stuck against a wall.

It works with instructions such as going forward, backward, turning and spinning.

`Motion` has several possible states:

* `GO`: the device is going forward or backward
* `SPIN`: the device is spinning left or right
* `TURN`: the device is turning (one wheel goes faster than the other)
* `STOP`: the device is stopping
* `NONE`: the device does not perform any action

So, if you need to wait until Moti has finished moving, you can basically wait for `Motion::getState()` to return `NONE`.

### `Light`

The `Light` API lets you control Moti's Leds.

The `Light` API runs in its own `thread` and is `non-blocking`.

All the `Led`s available are listed in the `LedIndicator` `enum` in `./lib/Moti/Moti.h`.

Currently, only fading a Led is available. It takes the `startColor`, the `endColor` and the `duration` of the fading.

It uses a `queue`, which means that you can *enqueue* multiple fades, and they will occur one after the other, *first in, first out*.

```cpp
// Fade heart led from red to blue in 3 seconds and a half
Light::fade(HEART, Light::RedPure, Light::BluePure, 3500);

// Then, fade heart led from blue to green in 1 second and a half
Light::fade(HEART, Light::BluePure, Light::GreenPure, 1500);
```

To get the current state of a Led, you can use `Light::getState(LedIndicator)`.

### `Moti`

The `Moti` API lets you monitor Moti's state regarding the environment.

The `Moti` API runs in its own thread and is `non-bloking`. It starts when Moti is powered up, so you can use it as is.

It lets you know if Moti is stuck, shaken or free falling for example.

### `Monitor`

The `Monitor` API lets you send data over a `Serial` port, USB or Bluetooth.

The `Monitor` API runs in its own `thread` and is `non-blocking`.

The data sent are:

* The motors direction (FORWARD|BACKWARD) and speed (0-255)
* The Leds data (State, R, G, B)
* The Sensors data:
    - Accelerometer (X, Y, Z)
    - Gyroscope (Yaw, Pitch, Roll, in degrees)

You can also send all data at once, with a `timestamp` (the number of milliseconds since power-up), in order to know when an event occurred or for data analysis.

For example:

```
A,1337;M,1,255,0,255;L,0,0,0,0;S,15,-12,235,0,34,29
```

**Explanation:**

*	`A,1337;` - `A` for "All data", 1337 is the number of seconds since power-up
*	`M,1,255,0,255;` - `M` for "Motors", `1,255` means that the right motor goes forward at max speed, `0,255` means that the left motor goes backward at max speed
*	`L,0,0,0,0;` - `L` for "Leds", the first `0` means that the led is inactive, and `0,0,0` is the color, black in this case
*	`S,15,-12,235,0,34,29;` - `S` for "Sensors", the rest of the data is quite
straightforward.

If you want to plot data, you can use our [moti-data-analysis](https://github.com/WeAreLeka/moti-data-analysis), a simple Python tool to plot data received from Moti.

## Anatomy of a program

### Directory structure

Before developing our own behavior, we are going to take a look at the main program running on Moti and see how things work together.

To begin with, open a `Terminal` window and go to moti's `src` directory:

```bash
$ cd /path/to/moti/src/moti
```

The directory structure is as follow:

```bash
.
├── lib
│   ├── Arbitrer
│   │   └── Arbitrer.h
│   └── Stabilization
│       └── Stabilization.h
├── Makefile
└── moti.cpp
```

Some explanations:

*	`moti.cpp` is the main program file that will be compiled for the robot - the name can change but must the same as its directory.
*	`Makefile` is the file used to compile the code.
*	`./lib` is the folder where you want to put the different `behaviors` needed for your program. You can put them all in `lib` or create sub directories, it depends on you. The more files you have the better it is to organize things properly.

### Threads and procedures

Each `behavior` has to run in its own `thread` with a `NORMALPRIO`. This ensures that Moti is able to run its own basic services.

Each behavior has a `msg_t thread(void* arg)` function and 3 procedures:

*	 `void start(void* arg=NULL, tprio_t priority=NORMALPRIO);`
*	 `void run(void);`
*	 `void stop(void);`

Let's dive in each of them.

#### The `start()` procedure

This procedure starts the `thread` that will run in the background. The code is basically the same for every `behavior`. When used, the `_isStarted` variable is set to `true` and the `_isRunning` boolean is set `false`. A `static thread` is then created.

```cpp
void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;
		_isRunning = false;

		(void)chThdCreateStatic(stabilizationThreadArea,
								sizeof(stabilizationThreadArea),
								priority, thread, arg);
	}
}
```

#### The `run()` procedure

This procedure tells the `thread` to perform its job normally: the `behavior` is active and running, and *Moti* is doing what has been written. When used, `_isRunning` is set to `true`.

```cpp
void run(void) {
    if (!_isStarted)
        start(NULL, NORMALPRIO);

	_isRunning = true;
}
```

#### The `stop()` procedure

This procedure tells the `thread` to stop it's job: the `behavior` is just paused and will not be killed, so you'll be able to start it again later. When used, `_isRunning` is set to `false`.

```cpp
void stop(void) {
	_isRunning = false;
}
```

#### The `thread` procedure

The `thread` function contains all the code of the `behavior`. Once the `thread` `_isStarted`, it waits for `_isRunning` to be true. Here is a basic example that you can fill later with your `behavior`:

```cpp
msg_t thread(void* arg) {
	while (!chThdShouldTerminate()) {
		if (_isRunning) {

		    /* Do your stuff there! */

		}

		waitMs(50); /* Prevents us from taking all the CPU */
	}

	return (msg_t)0;
}
```

## Building a basic example

### Introduction

To better understand how it works, we are now going to write a small example, with the `Stabilization` behavior.

The complete example is available in [`test/BehaviorExample`](https://github.com/WeAreLeka/moti/tree/dev/test/BehaviorExample), for those who don't want to wait.

For the others, we are going to write the code step by step.

### Stabilization?!

Children love to hold and play with Moti. They often try to put it upside down in the sphere or to make it spin. That's why we want Moti to be stabilized, and always have his wheels facing the floor.

Basically, we will face two case of rotation:

*	Rotation around the *Y axis* - the `X acceleration` value will change - Moti has to go forward or backward to find his stable position
*	Rotation around the *X axis* - the `Y acceleration` value will change - Moti has to perform a 90° rotation before going forward or backward to find his stable position

Now that we know what we want to do, we are going to implement it. Don't worry, the maths behind that are pretty basic. :)

### Let's code!

#### Creating the files and the directories

First we are going to create all the files we will need:

```bash
# go to moti's directory
$ cd /path/to/moti

# go to the src directory
$ cd src

# create a new directory for our example and go to this new directory
$ mkdir BehaviorExample && cd $_

# create the main program file
$ touch BehaviorExample.cpp

# create lib directory
$ mkdir -p lib/Stabilization

# create the stabilization files
$ touch lib/Stabilization/Stabilization.h lib/Stabilization/Stabilization.cpp
```

And that's it! We now have all the files we will use in the next steps.

#### The `Stabilization` behavior

We will start with the `Stabilization` behavior and use the basic code we saw earlier.

In your favorite text editor, open the file `./lib/Stabilization/Stabilization.h`.

We want to:

*	include the required headers
*	create a `namespace` called `Stabilization`
*	create our functions prototypes and useful variables

You can copy/paste the following in `./lib/Stabilization/Stabilization.h`:

```cpp
#include <Arduino.h>
#include "ChibiOS_AVR.h"
#include "Configuration.h"

namespace Stabilization {

	// Functions
	static msg_t thread(void* arg);
	void start(void* arg=NULL, tprio_t priority=NORMALPRIO);
	void run(void);
	void stop(void);

	// Variables
	static WORKING_AREA(stabilizationThreadArea, 256);
	bool _isStarted = false;
	bool _isRunning = false;

}
```

Now we are going to write the functions definition in `./lib/Stabilization/Stabilization.cpp`. Note that we could write both in `.h` but as your code gets bigger and more complex, it is better to keep things separated.

We start with the 3 basic procedures `start()`, `run()` and `stop()`. You can copy/past the following inside `./lib/Stabilization/Stabilization.cpp`:

```cpp
#include "Stabilization.h"

namespace Stabilization {

	// Definition of the start() procedure
	void start(void* arg, tprio_t priority) {
		if (!_isStarted) {
			_isStarted = true;
			_isRunning = true;

			(void)chThdCreateStatic(stabilizationThreadArea,
									sizeof(stabilizationThreadArea),
									priority, thread, arg);
		}
	}

	// Definition of the run() procedure
	void run(void) {
		if (!_isStarted)
			start(NULL, NORMALPRIO);

		_isRunning = true;
	}

	// Definition of the stop() procedure
	void stop(void) {
		_isRunning = false;
	}

	msg_t thread(void* arg) {
		while (!chThdShouldTerminate()) {
			if (_isRunning) {

				/* We will write the code here */

			}

			waitMs(50); /* Prevents the thread from using all the MCU */
		}

		return (msg_t)0;
	}

}
```

Now we are going to write the actual stabilization code.

If Moti is rocked back and forth, the `input` is the `X-axis` value of the accelerometer. We use it to provide a proportional `output` value to the motors. We want the `output` value to be half the `input` value. Therefor, the coefficient is `0.5` and `outputValue = 0.5 * inputValue`. If the `input` value is negative, the motors will go backward.

When the `Y-axis` exceeds a threshold of `80`, we tell Moti to spin 90°.

We also need to prevent the motors from running all the time, so we add a little constraint: the absolute `output` value has to be greater than `100` for the motor to roll.

You can copy/past the following to replace `msg_t thread (void* arg) {...}`:

```cpp
msg_t thread(void* arg) {

    float inputValue = 0.f;             // Define variables
    float outputValue = 0.f;

    float accY = 0.f;                   // The Y-axis accelerometer value
    SpinDirection spinDirection;        // Spin direction i.e. left or right

    Direction direction;
    uint8_t speed;

	while (!chThdShouldTerminate()) {

		if (_isRunning) {
		    inputValue = Sensors::getAccX();  // Get the value of the X-axis
		    outputValue = 0.5 * inputValue;   // Compute the output value

		    accY = Sensors::getAccY();        // Get the value of the Y-axis

		    if (abs(outputValue) > 100.f) {
		        direction = outputValue < 0.f ? BACKWARD : FORWARD;    // Select the direction
		        speed = (uint8_t)abs(outputValue);

		        Motion::go(direction, speed, 100);    // Turn the motors on for 100ms at the desired speed
		    }
		    else if (abs(accY) > 80.f) {
	            spinDirection = accY > 0.f ? RIGHT : LEFT;

	            Motion::spinDeg(spinDirection, 130, 90);       // Spin 90 degrees with an arbitrary speed of 130
		    }
		}

		waitMs(50); // Prevents us from taking all the CPU

	}

	return (msg_t)0;
}
```


That's it! We now have our first behavior!

#### The `main thread`

The `main thread` is the entry point of every program made for Moti. It here that all the basic behaviors, services and API are loaded. It's also there that you decide to use or not some behaviors, and how you want them to interact.

You need three parts:

*	first part to `init` all the basic services
*	second part to `init` your new behaviors
*	third part to set the `workflow` of your application

To show you an example, in the following code, we turn on and off the `Stabilization` behavior when Moti `isShaken()`.

You can copy/past the following inside of `./BehaviorExample.cpp`:

```cpp
#include <Arduino.h>
#include <Wire.h>

#include "Motion.h"
#include "Moti.h"
#include "Light.h"
#include "Communication.h"
#include "Serial.h"

#include "./lib/Stabilization/Stabilization.h"

void chSetup() {

    // Init part
    Sensors::init();
    Drive::start();
    DriveSystem::start();
    Moti::start();
    Light::start();

	// Init our new behavior
    Stabilization::start();

	// Set variables
    bool stabilize = false;

    while (TRUE) {
        if (Moti::isShaken()) {
            if (!stabilize)
                Stabilization::run();
            else
                Stabilization::stop();

            stabilize = !stabilize;
        }

        waitMs(50);
    }
}
```

## Go further, multiple behaviors

Now that we built a stabilization behavior, let's go a bit further and add
another behavior: a LED will fade if Moti is falling (maybe to warn us it
is going to be hurt, good boy...). The behavior will be named `FadeBehavior`
during the rest of the example.

So, first, let's code up the behavior telling Moti to fade his heart,
which is not really hard:

```
msg_t thread(void* arg) {
	while (!chThdShouldTerminate()) {
		if (_isRunning) {
		    /* Red to orange, for 1 sec and a half */
		    if (Light::getHeartState() == INACTIVE)
		        Light::fadeHeart(Color::RedPure, Color::Orange, 1500);
		}

		waitMs(50); /* Prevents us from taking all the CPU */
	}

	return (msg_t)0;
}
```

That's it, we're done with this basic behavior, now let's integrate it
to the main thread. Remember, when Moti falls, the behavior must be ran,
otherwise it must be stopped.

```
void chSetup() {
    /* Init part */
    Sensors::init();
    Drive::start();
    DriveSystem::start();
    Moti::start();
    Light::start();

    Stabilization::start();
    bool stabilize = false;

    /* Start our new behavior */
    FadeBehavior::start();
    bool fade = false;

    while (TRUE) {
        if (Moti::isShaken()) {
            if (!stabilize)
                Stabilization::run();
            else
                Stabilization::stop();

            stabilize = !stabilize;
        }

        if (Moti::isFalling()) {
            FadeBehavior::run();
            fade = true;
        }
        else {
            if (fade) {
                FadeBehavior::stop();
                fade = false;
            }
        }

        waitMs(50);
    }
}
```


Here we are, Moti now has two behaviors living side by side, each one is
activated when the environment changes, meaning that Moti reacts to its
environment, that mainly what it has been built for :)


That's it, you now are able to build your own behaviors and have lots
of fun with your Moti device!

Bye.






