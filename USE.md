# How to develop behaviors for Moti

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

*	`A,1337`: `A` for "All data", 1337 is the number of seconds since power-up
*	`M,1,255,0,255`: `M` for "Motors", `1,255` means that the right motor goes forward at max speed, `0,255` means that the left motor goes backward at max speed
*	`L,0,0,0,0`: `L` for "Leds", the first `0` means that the led is inactive, and `0,0,0` is the color, black in this case
*	`S,15,-12,235,0,34,29`: `S` for "Sensors", the rest of the data is quite
straightforward.

If you want to plot data, you can use our [moti-data-analysis](https://github.com/WeAreLeka/moti-data-analysis), a simple Python tool to plot data received from Moti.

## Anatomy of a program

Before developing our own behavior, we are going to take a look at the main program running on Moti and see how things work together.

To begin with, open a `Terminal` window and go to moti's `src` directory:

```Shell
$ cd /path/to/moti/src/moti
```

The directory structure is as follow:

```Shell
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
*	`Makefile` is the filed use for compilation
*	`./lib` is the folder where you want to put the different `behaviors` needed for your program. You can put them all in `lib` or create sub directories, it depends on you. The more files you have the better it is to organize things properly

Each `behavior` has to run in its own `thread` with a `NORMALPRIO`, in order for Moti to run its own basic services.

Each behavior has a `msg_t thread(void* arg)` function and 3 procedures:

*	 `void start(void* arg=NULL, tprio_t priority=NORMALPRIO);`
*	 `void run(void);`
*	 `void stop(void);`

Let's dive in each of them.

### The `start()` procedure

This procedure is here to start the `thread` that will run in background and the code is basically the same for every `behavior`. When used, the `_isStarted` variable must be set to `true` and the `_isRunning` boolean must be set `false`. A `static thread` is then created.

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

### The `run()` procedure

This precedure tells the `thread` to peform its job normally: the `behavior` is active and running, and *Moti* is doing what has been written. When used, `_isRunning` is set to `true`.

```cpp
void run(void) {
    if (!_isStarted)
        start(NULL, NORMALPRIO);

	_isRunning = true;
}
```

### The `stop()` procedure

This procedure tells the `thread` to stop it's job: the `behavior` is just paused and will not be killed, so you'll be able to start it again later. When used, `_isRunning` is set to `false`.

```cpp
void stop(void) {
	_isRunning = false;
}
```

Once you have these three procedures up and working, you will be able to start
developping your behavior!

### The `thread` procedure

The `thread` function containes all the code of the `behavior`. Once the `thread` `_isStarted`, it waits for `_isRunning` to be true. Here is a basic example that you can fill later with your `behavior`:

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

## Building a basic example, the Stabilization behavior

Let's now go and build our first small example behavior, a **Stabilization** behavior!


You can develop your behavior as you intend to, but the solution we opted for is as follows:

* Create a directory in the `lib` folder
* Create a header file within this directory
* Create the working area for the thread (e.g: `static WORKING_AREA(threadArea, 256)`)
* In this header, create a namespace having the name of your new behavior
(e.g: `namespace Stabilization`)
* Create 3 procedures:
    - `void start(void* arg=NULL, tprio_t priority=NORMALPRIO);`
    - `void run(void);`
    - `void stop(void);`
* Add two boolean variables:
    - `bool _isStarted = false;`
    - `bool _isRunning = false;`
* Create the thread function `msg_t thread(void* arg)`
* You are ready to code!



### What do I mean with "Stabilization"?

Well, Moti is spherical, with wheels within the sphere, when someone lifts it and
plays with it in his hands (like checking it out, turning in), we want Moti to
stabilize, this means that its wheels always have to "face the floor", when it is
rotated along its X-axis, it will go forward or backward in order to balance itself.
And if it is rotated along its Y-axis, we will let Moti perform a 90-degrees rotation,
then letting it go forward or backward.

### Here we go!

We will start with the basic code we saw earlier:

```
void start(void* arg, tprio_t priority) {
	if (!_isStarted) {
		_isStarted = true;
		_isRunning = true;

		(void)chThdCreateStatic(stabilizationThreadArea,
								 sizeof(stabilizationThreadArea),
								 priority,
								 thread,
								 arg);
	}
}

void run(void) {
    if (!_isStarted)
        start(NULL, NORMALPRIO);

	_isRunning = true;
}

void stop(void) {
	_isRunning = false;
}

msg_t thread(void* arg) {
	while (!chThdShouldTerminate()) {
		if (_isRunning) {
		    /*  We will build our code here */
		}

		waitMs(50); /* Prevents us from taking all the CPU */
	}

	return (msg_t)0;
}
```

We may also need some extra variables, an input and an output integers.

Basically, the input will be the X-axis value of the accelerometer, and
we will provide a proportional output to the device. Here, we will opt for
an output equals to the half of the input, this means that it the accelerometer
returns a value of 212, Moti will go forward with a speed of 106. If the input
is negative, this just means that we will have to go backward in order to
stabilize.

We will also need to prevent the motors from running all the time, so let's add
a little constraint: if the output is less than 100, we will assume that we already
are stabilized won't do anything for this X-axis.

```
msg_t thread(void* arg) {
    float input = 0.f;
    float output = 0.f;

    Direction direction;
    uint8_t speed;

	while (!chThdShouldTerminate()) {
		if (_isRunning) {
		    input = Sensors::getAccX();  // Retrive the value of the X-axis
		    output = 0.5 * input;

		    if (abs(output) > 100.f) {
		        direction = output < 0.f ? BACKWARD : FORWARD;
		        speed = (uint8_t)abs(output);

		         // Just go for 100ms, this will be discarded later if we
		         // need to change the output speed
		        Motion::go(direction, speed, 100);
		    }
		}

		waitMs(50); /* Prevents us from taking all the CPU */
	}

	return (msg_t)0;
}
```

Great! Now we can response to a change with the X-axis of the accelerometer.
Last step now is to handle the Y-axis change. When the Y-axis exceeds a given
threshold (let's say 80 here), we will tell Moti to spin for 90 degrees.

Let's code this up!

```
msg_t thread(void* arg) {
    float input = 0.f;
    float output = 0.f;

    Direction direction;
    uint8_t speed;

    float accY = 0.f; // The value of the Y-axis of the accelerometer
    SpinDirection spin; // The direction in which Moti will spin, if it has to

	while (!chThdShouldTerminate()) {
		if (_isRunning) {
		    input = Sensors::getAccX();  // Retrive the value of the X-axis
		    output = 0.5 * input;

		    accY = Sensors::getAccY();

		    if (abs(output) > 100.f) {
		        direction = output < 0.f ? BACKWARD : FORWARD;
		        speed = (uint8_t)abs(output);

		         // Just go for 100ms, this will be discarded later if we
		         // need to change the output speed
		        Motion::go(direction, speed, 100);
		    }
		    else if (abs(accY) > 80.f)
	            spin = accY > 0.f ? RIGHT : LEFT;

	            // Spin 90 degrees with an arbitrary speed of 105
	            Motion::spinDeg(spin, 105, 90);
		    }
		}

		waitMs(50); /* Prevents us from taking all the CPU */
	}

	return (msg_t)0;
}
```


Here it is, we now have our first behavior! It only took us a few lines to
have a basic, working, one.

## The main thread

The main thread will be the entry point of Moti, where all basic behaviors and
API are loaded, and where you can decide to use or not some behaviors, and how
you want them to interract.

An example main thread can be found in `src/moti/moti.cpp`

Let's build our main thread for our new Stabilization behavior:

```
void chSetup() {
    /* Init part */
    Sensors::init();
    Drive::start();
    DriveSystem::start();
    Moti::start();
    Light::start();

    /* Start our brand new behavior */
    Stabilization::start();

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

Maybe you guessed what happended here, the flow is quite easy:
* First, Moti does not do anything
* It we shake it, Moti enters its stabilization behavior
* If we shake it again, Moti stop this behavior
* Repeat...


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






