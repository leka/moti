#Moti Readme


##About

Moti is a new kind of interactive smart toy: it's a spherical robot specially designed for children with autism.


##Why Github?

Because our team is not located in one single place, we needed a way to distribute the process of prototyping so that everyone could try it at home, debug it and create new features.

At first, we wanted to keep the code for ourselves. But then we thought "hey! our project is great, but wouldn't it be better if a lot of people could fork it, add their modifications, features, improvements, and then share it back to the community?"

For us, the answer is an absolute YES! We want people to be able to look at our code, use it for their projects, use it to build their own Moti and then get back to us to improve the awesomeness for a better world today!


##Actual Version

We are now working with `MOTI v1.0`.

From now on, the old moti versions (moti_1 & moti_2) are **deprecated** and will only be accessible from the `oldies` branch [here](https://github.com/WeAreLeka/moti/tree/oldies).

We are building a super class called `MOTI` to simplify the development of the robot behaviors. To put it in a nut shell, it will look like that:

	Moti.goForward(); //Moti goes forward
	Moti.stop();
	Moti.spinRight();
	Moti.blinkLed(5); //the led blink 5 times
	Moti.checkSensors();
	Moti.sendData();


##Branches

**IMPORTANT:** Our model is based on [A successful Git branching Model](http://nvie.com/posts/a-successful-git-branching-model/). PLEASE, take the time to read it carefully before starting. We don't want you to mess things up! :)

*	master is the stable branch for production and tests.
*	dev (origin HEAD) is the development branch for unit/lab tests and behaviour development. if the lab tests are concluding, a pull request to the master can be made.
*	feature branches are transitory branches used to develop new features to incorporate to the dev branch. when the feature is bugless, a pull request may be made to merge the concluding results inside the dev branch.


##Toolbox

###Basic

To help us develop our product, you'll first need to different softwares:

*	[Arduino IDE](http://arduino.cc/en/main/software) - this software is used to develop the source code and to upload it to your Arduino board. We recommend going for the 1.0.5 version. If you are a little more advanced user feel free to try the new beta version 1.5. Please note that you may encounter strange behaviors (we do sometimes), so please, take the time to report them in the [Due Forum](http://forum.arduino.cc/index.php?board=87.0) and/or here.
*	[Processing IDE](http://www.processing.org/download/) - this software is an incredible tool to create GUI from scratch. Besides Moti, we are developing a GUI to debug and analyze data. You can find the [Moti Processing App here](https://github.com/WeAreLeka/moti-processing-app). As for the Arduino IDE, we are using the latest beta. Sometimes everything works find, sometimes there are some bugs. Restarting your computer can be a good solution.
*	[Git](http://git-scm.com/) - Of course, you need to have git install but we assume that if you are reading this, you know what it is and how to use it. If you're not really comfortable with the Terminal, you can use a Git GUI. [Try this list](http://git-scm.com/download/gui/mac), test them and stick to the one you prefer! :)
*	[Github account](https://github.com/signup/free) - Sign up for free, fork the project, improve the awesomeness and pull it back!

With these softwares, you should be up and running and ready to hack autism with Moti!


###Advanced

Okay, so you started with the Arduino and Processing IDE, you're now familiarized with the languages, you've already read and write something like a thousand lines of code and you would really love some new tools to speed up your coding and improve your coding experience. Here are some solutions for you that we, at Leka, are using on a daily basis with great pleasure!

*	[Sublime Text 2](http://www.sublimetext.com/2) - ST2 is our favorite code editor. It takes some time to familiarize but once you get used to it, you'll have some hard time finding a replacement! The great thing with ST2 is that you can install or develop your own packages to improve your coding experience. Here after are some of theme :)
*	[ST2 Package Controler](http://wbond.net/sublime_packages/package_control) - First start with this one! It will allow you to manage and install great packages. Follow the instruction provided by the link and your good to go!
*	[Arduino-like IDE](https://github.com/Robot-Will/Stino) - This package allow you to develop the Arduino code and upload it to your robot directly from within ST2. Everything is very well explained on their Github. If you are having some troubles, give us a call or contact them directly.
*	[Processing-like IDE](https://github.com/b-g/processing-sublime) - Same as above but for Processing!


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

The library is Copyright (c) 2013 Leka Inc., and distributed under the MIT License as follows:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

###Additional License

"THE BEER-WARE LICENSE" (Revision 42):
<hello@weareleka.com> wrote this file. As long as you retain this notice you can do whatever you want with this stuff. If we meet some day, and you think this stuff is worth it, you can buy me a beer in return.


##Leka would like to thank

Our team would like to thank with all our hearts [Vincent Thiberville](http://www.vincent-thiberville.com/) for his kind work on our first prototype.
Without him nothing would have been possible!
