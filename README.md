[![Stories in Ready](https://badge.waffle.io/WeAreLeka/moti.png?label=ready)](http://waffle.io/WeAreLeka/moti)

#Moti Readme

##About

Moti is a new kind of interactive smart toy: it's a spherical robot specially designed for children with autism.

##Why Github?

Because our team is not located in one single place, we needed a way to distribute the process of prototyping so that everyone could try it at home, debug it and create new features.

At first, we wanted to keep the code for ourselves. But then we thought "hey! our project is great, but wouldn't it be better if a lot of people could fork it, add their modifications, features, improvements, and then share it back to the community?"

For us, the answer is an absolute YES! We want people to be able to look at our code, use it for their projects, use it to build their own Moti and then get back to us to improve the awesomeness for a better world today!

## TO DO

### Global

*	~~make this project more collaborative~~ - DONE :)
*	implement a real list of all the tasks we need to do to make the robot work!

### Sensors

*	~~integrate the new version of FreeIMU~~ - DONE
*	~~make the appropriate changes to get rid of all the useless libs~~ - DONE
*	implement the sensor analyser to find pattern in the sensors' data
*	compute moving average
*	compute square value

### Motors

*	~~separate de Motors Class in 2 clases: Motor et DriveSystem to better separate concerns~~ - DONE
*	~~unit test motor class~~ - DONE
*	test for minimum motor speed
*	use sensors data for `spinRight` and `spinLeft`

### Behaviors

*	develop stabilize behavior
*	develop affraid behavior
*	develop happy behavior
*	develop seeking interaction behavior
*	develop stuck behavior
*	develop hit a wall behavior

### Moti

*	~~try and implement a RTOS using ChibiOS or NilRTOS~~ - DONE - ChibiOS has been chosen and is up and running

### Hardware

*	design the PCB
*	3D print the robot

##Actual Version

We are now working with `MOTI v1.0`.

From now on, the old moti versions (moti_1 & moti_2) are **deprecated** and will only be accessible from the `oldies` branch [here](https://github.com/WeAreLeka/moti/tree/oldies).

We are building a super class called `MOTI` to simplify the development of the robot behaviors. To put it in a nut shell, it will look like that:

```C++
motors.goForward(); //Moti goes forward
motors.stop();
motors.spinRight();
led.blinkLed(5); //the led blink 5 times
sensors.read();
Moti.sendData();
```

It is a lot easier for everyone to write code and to understand what you do. It is also easier for the other people who will read your code to understand what you're trying to do.

It's not a real `API` but it will eventually become one.

##Branches

**IMPORTANT:** Our model is based on [A successful Git branching Model](http://nvie.com/posts/a-successful-git-branching-model/). PLEASE, take the time to read it carefully before starting. We don't want you to mess things up! :)

*	`master` is the stable branch for production and tests.
*	`dev` (origin HEAD) is the development branch for unit/lab tests and behaviour development. if the lab tests are concluding, a pull request to the master can be made.
*	`feature branches` are transitory branches used to develop new features to incorporate to the dev branch. when the feature is bugless, a pull request may be made to merge the concluding results inside the dev branch.
*	`oldies` branch keeps all the old code and libraries we used for the first prototype. It is deprecated now but could be help full for beginners.

##How to install

The full procedure is detailed in [INSTALL.md](./INSTALL.md). It has been written for beginners as well as for advanced hackers.

##How to use

The full procedure on how to use everything you've just installed is described in [USE.md](./USE.md).

##How to contribute

Thanks to Github, the best way to help us is by `forking` the project, coding and then making pull requests.

We will only accept direct merging of pull request, so make sure your code is OK for that.

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
