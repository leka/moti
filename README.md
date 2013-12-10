#Moti Readme


##About

Moti is a new kind of interactive smart toy: it's a spherical robot specially designed for children with autism.


##Why Github?

Because our team is not located in one single place, we needed a way to distribute the process of prototyping so that everyone could try it at home, debug it and create new features.

At first, we wanted to keep the code for ourselves. But then we thought "hey! our project is great, but wouldn't it be better if a lot of people could fork it, add their modifications, features, improvements, and then share it back to the community?"

For us, the answer is an absolute YES! We want people to be able to look at our code, use it for their projects, use it to build their own Moti and then get back to us to improve the awesomeness for a better world today!


## TO DO

### Global

*	make this project more collaborative :)
*	implement a real list of all the tasks we need to do to make the robot work!

### Sensors

*	~~integrate the new version of FreeIMU~~ - DONE
*	make the appropriate changes to get rid of all the useless libs
*	implement the sensor analyser to find pattern in the sensors' data
*	compute moving average
*	compute square value

### Motors

*	separate de Motors Class in 2 clases: Motor et DriveSystem to better separate concerns
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

*	try and implement a RTOS using ChibiOS or NilRTOS

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


##Known Issues

None yet.


##TODO

*	Document the code
*	Generate documentation with Doxygen


##Copyright and License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Moti - Spherical Autonomous Rolling Robot for Children with Autism</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="http://weareleka.com" property="cc:attributionName" rel="cc:attributionURL">Ladislas de Toldi for Leka</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.<br />Based on a work at <a xmlns:dct="http://purl.org/dc/terms/" href="http://github.com/WeAreLeka/Moti" rel="dct:source">http://github.com/WeAreLeka/Moti</a>.


