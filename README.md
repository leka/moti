Moti Readme
=======================


About
-----

Because our team is not located in one single place, we needed a way to distribute the process of prototying so that everyone could try it at home, debug it and create new features.

At first, we wanted to keep the code for ourselves. But then we thought "hey! our project is great, but wouldn't it be better if a lot of people could fork it, add their modifications, features, improvements, and then share it back to the community?"

For us, the answer is an absolute YES! We want people to be able to look at our code, use it for their projects, use it to build their own Moti and to improve the awesomeness for a better world today!


Branches
------------

*	master is the stable branch for production and tests on the children.
*	dev is the development branch for unit/lab tests and behaviour developpment. if the lab tests are concluding, a pull request to the master can be made.
*	raw is the "original" branch. it containes all the original source files. those are very, very, very important and can save us in case something goes wrong. Therefore, it is absolutely forbidden to use and/or modify the raw branch. Be advised!
*	feature branches are transitory branches used to developp new features to incorporate to the dev branch. when the feature is bugless, a pull request may be made to merge the concluding results inside the dev branch.


Known Issues
------------

*	none yet (we're so cool!)


Installing & Updating
---------------------

Note: Make sure Git and cURL are installed.

For the project, we use different libraries. Some of them are public, well-known libraries from the Arduino website and some are custom made to suit our needs.
If you want to be able to compile the project, you need to have our libraries inside your library folder so they can be accessed by the Arduino app.
[Following this link](http://arduino.cc/en/Guide/Libraries), you'll know here to find yours depending on your OS: Windows or a UNIX based system (OS X, Linux, Debien, etc.)

###Stable on Linux/Unix based systems using make install####

####Installing

The following instructions should work on Mac OS X, Debian, Ubuntu, Fedora, RedHat, etc.

The easiest way is to use Git and make for installing:

	$ git clone https://github.com/LekaSmartToys/robot.git
	$ cd YOUR/PATH/TO/robot/
	$ git checkout dev #or master
	$ make install

####Updating

Updating using git

	$ git pull
	$ make cleaninstall


Uninstalling 
------------

###Linux/Unix based OS

To remove all the libraries used for the Moti project, simply run:
	
	$ git pull
	$ make clean


Leka would like to thank
------------------------

Our team would like to thank with all our hearts [Vincent Thiberville](http://www.vincent-thiberville.com/) for his kind work on our first prototype.
Without him nothing would have been possible!


Copyright and License
---------------------

The library is Copyright (c) 2013 Leka Inc., and distributed under the MIT
License as follows:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Additional License
---------------------

"THE BEER-WARE LICENSE" (Revision 42):
[Leka](hello@weareleka.com) wrote this file. As long as you retain this notice you can do whatever you want with this stuff. If we meet some day, and you think this stuff is worth it, you can buy me a beer in return.
