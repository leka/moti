[![Stories in Ready](https://badge.waffle.io/WeAreLeka/moti.png?label=ready)](http://waffle.io/WeAreLeka/moti)

=======

#Moti Readme

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [](#)
- [Moti Readme](#moti-readme)
	- [About](#about)
	- [Why Github?](#why-github)
	- [Is Moti open source and/or open hardware](#is-moti-open-source-andor-open-hardware)
	- [TO DO](#to-do)
		- [Global](#global)
		- [Sensors](#sensors)
		- [Motors](#motors)
		- [Behaviors](#behaviors)
		- [Hardware](#hardware)
	- [Actual Version](#actual-version)
	- [Branches](#branches)
	- [How to install](#how-to-install)
	- [How to use](#how-to-use)
	- [How to contribute](#how-to-contribute)
	- [How to make your own Moti](#how-to-make-your-own-moti)
	- [Copyright and License](#copyright-and-license)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

##About

Moti is a new kind of interactive smart toy: it's a spherical robot specially designed for children with communication and social disabilities.

##Why Github?

At first, we wanted to keep the code for ourselves. But then we thought "hey! our project is great, but wouldn't it be better if a lot of people could fork it, add their modifications, features, improvements, and then share it back to the community?"

For us, the answer is an absolute **YES**! We want people to be able to look at our code, use it for their projects, use it to build their own Moti and then get back to us to improve the awesomeness for a better world today!

## Is Moti open source and/or open hardware

**Short answer:** yes.

**Long answer:** yes, Moti's software is and will continue to be open source. Reasons are numerous, but the three main reasons are:

*	we love open source, we use it constantly, we use GPL libraries, we want to keep that going on
*	we truly believe we can create a community around our project, composed of parents, developers, researchers, doctors, carers
*	because we just want to

For the hardware, things are a little different. Today, we use Arduino as our prototype platform. The documentation to build your own Moti is a little outdated and will be updated soon. It will be available for anyone who wants to build it's own Moti. If we have enough time, we will also offer a way to download or order 3D printed pieces to assemble the robot.

In the meantime we are working on a *more robust, more powerful, more sensors* prototype. We haven't decided yet if this new version will be open hardware, but we are currently looking and the pros and cons.

## TO DO

### Global

*	~~make this project more collaborative~~ - DONE :)
*	implement a real list of all the tasks we need to do to make the robot work! - WIP

### Sensors

*	~~integrate the new version of FreeIMU~~ - DONE
*	~~make the appropriate changes to get rid of all the useless libs~~ - DONE
*	implement the sensor analyser to find pattern in the sensors' data - WIP

### Motors

*	~~separate de Motors Class in 2 clases: Motor et DriveSystem to better separate concerns~~ - DONE
*	~~unit test motor class~~ - DONE
*	~~test for minimum motor speed~~- CANCELED - too hard to do with our current motors...
*	use sensors data for `spinRight` and `spinLeft`

### Behaviors

*	~~try and implement a RTOS using [ChibiOS/RT](#link) or [NilRTOS](#link)~~ - DONE - ChibiOS has been chosen and is up and running
*	develop stabilize behavior - WIP
*	develop afraid behavior
*	develop happy behavior
*	develop seeking interaction behavior
*	develop stuck behavior
*	develop hit a wall behavior - WIP

### Hardware

*	design the PCB - WIP
*	3D print the robot

##Actual Version

We are now working with `MOTI v1.0`.

From now on, the old moti versions (moti_1 & moti_2) are **deprecated** and will only be accessible from the [`oldies` branch](https://github.com/WeAreLeka/moti/tree/oldies).

For today, building a robot behavior is as simple as:

```C++
motors.go();

delay(2500);

motors.stop();

sensors.read();
sensors.sendData();
```

It is a lot easier for everyone to write code and to understand what you do. It is also easier for the other people who will read your code to understand what you're trying to do.

It's not a real `API` but it will eventually become one.

##Branches

**IMPORTANT:** Our model is based on [A successful Git branching Model](http://nvie.com/posts/a-successful-git-branching-model/). PLEASE, take the time to read it carefully before starting. We don't want you to mess things up! :)

*	`master` is the stable branch for production.
*	`dev` (origin HEAD) is the development branch for unit/lab tests and behavior development. If the lab tests are concluding, a pull request to the master can be made.
*	`feature branches` are transitory branches used to develop new features to incorporate to the dev branch. When the feature is bug free, a pull request can be made to merge the concluding results inside the dev branch.
*	`oldies` branch keeps all the old code and libraries we used for the first prototype. It is deprecated now but could be help full for beginners.

##How to install

The full procedure is detailed in [INSTALL.md](./INSTALL.md). It has been written for beginners as well as for advanced hackers.

##How to use

The full procedure on how to use everything you've just installed is described in [USE.md](./USE.md).

##How to contribute

Thanks to Github, the best way to help us is by `forking` the project, coding and then making pull requests.

We will only accept direct merging of pull request, so make sure your code is OK for that.

## How to make your own Moti

Moti is currently based on Arduino. That's why it is totally open hardware and the full bill of materials will be added soon.

The Arduino Mega2560 is becoming a little tight to suit our power and memory needs. We are currently benchmarking different alternatives such as the [Olimex STM32-H407](#link).

In the meantime we are also working with the [Criif](#link) to build custom prototype with a lot of different sensors and actuators and even a real OS (Bare metal is cool but imagine what we could do with Linux!).

##Copyright and License

Moti, a free, as in speech, robotic spherical mobile robot for children with autism.

Copyright (C) 2013 Ladislas de Toldi (ladislas at weareleka dot com)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see [http://www.gnu.org/licenses/].
