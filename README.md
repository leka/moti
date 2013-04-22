Robot Readme
=======================

*	&copy; Leka Smart Toys, hello@weareleka.com, 2012-2013
*	The code presented here is a property of Leka Smart Toys.


Summary
-------

robot is the code name of our first home made prototype of Moti.


About
-----

Because our team is not located in one single place, we needed a way to distribute the process of prototying so that everyone could try it at home, debug it, create new features and improve the awesomeness for a better world today!


Branches
------------

*	master is the stable branch for production and tests on the children.
*	dev is the development branch for unit/lab tests and behaviour developpment. if the lab tests are concluding, a pull request to the master can be made.
*	raw is the "original" branch. it containes all the original source files. those are very, very, very important and can save us in case something goes wrong. Therefore, it is absolutely forbidden to use and/or modify the raw branch. Be advised!
*	feature branches are transitory branches used to developp new features to incorporate to the dev branch. when the feature is bugless, a pull request may be made to merge the concluding results inside the dev branch.


Known Issues
------------

*	none yet (we're so cool!)


Installing
----------

###Stable on Linux/Unix based systems using make####

Note: Make sure Git and cURL are installed.

For the project, we use different libraries. Some of them are public, well-known libraries from the Arduino website and some are custom made to suit our needs.
If you want to be able to compile the project, you need to have your libraries inside the library folder of accessed by the Arduino app.
[Following this link](http://arduino.cc/en/Guide/Libraries), you'll know here to find yours depending on your OS: Windows or a UNIX  based system (OS X, Linux, Debien, etc.)

The following instructions should work on Mac OS X, Debian, Ubuntu, Fedora, RedHat, etc.

The easiest way is to use Git and make for installing:

	$ git clone https://github.com/LekaSmartToys/robot.git
	$ cd YOUR/PATH/TO/robot/
	$ git checkout master
	$ make install

Updating using git

	$ git pull
	$ make install


Leka would like to thank
------------------------

Our team would like to thank with all our hearts [Vincent Thiberville](http://www.vincent-thiberville.com/) for his kind work on our first prototype.
Without him nothing would have been possible!
