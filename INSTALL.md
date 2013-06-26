#Moti Installation Guide


##About

Here is the guide to correctly setup all you need to peacefully develop awesome code for Moti. Usually, you won't find instructions as detailed as this one, because it's part of the "hacker thing" to know what you're doing and/or to make it work by trials and errors.

That could work for us, but it's a little different. This project is not a small part in a bigger project. It actually is the bigger project and here after you'll find all the steps to successfully code/debug/compile/upload/test everything on your own robot.

The thing is, it took us quite some time to figure out what to do, how to do it, which Homebrew `formula` to install, how to use the makefile and so on. When we say quite some time, you can count full working weeks of reading, trying, trying again, cursing because nothing is working, dead ends, new ideas, clearer vision and finally a working process.

It's our present to the world!

You can follow two directions: the detailed way (perfect for beginners) or the more advanced way (perfect for highly talented hackers).

Have fun! :)


##Toolbox


###Basic

To help us develop our product, you'll first need to install different softwares:

*	[Arduino IDE](http://arduino.cc/en/main/software) - this software is used to develop the source code and to upload it to your Arduino board. We recommend going for the 1.0.5 version. If you are a little more advanced user feel free to try the new beta version 1.5. Please note that you may encounter strange behaviors (we do sometimes), so please, take the time to report them in the [Due Forum](http://forum.arduino.cc/index.php?board=87.0) and/or here.
*	[Homebrew](http://mxcl.github.io/homebrew/) - Homebrew is our best package manager for OS X (a Linux version is under development). Homebrew helps you download and install packages to do whatever your need to do, without compromising your computer and the weird stuff going on in `/usr/local/`
*	[Git](http://git-scm.com/) - Of course, you need to have git install but we assume that if you are reading this, you know what it is and how to use it. If you're not really comfortable with the Terminal, you can use a Git GUI. [Try this list](http://git-scm.com/download/gui/mac), test them and stick to the one you prefer! :)
*	[Github account](https://github.com/signup/free) - Sign up for free, fork the project, improve the awesomeness and pull it back!

With these softwares, you should be up and running and ready to hack autism with Moti!


###Advanced

Okay, so you started with the Arduino IDE, you're now familiarized with the languages, you've already read and write something like a thousand lines of code and you would really love some new tools to speed up your coding and improve your coding experience. Here are some solutions for you that we, at Leka, are using on a daily basis with great pleasure!

*	[Sublime Text 2](http://www.sublimetext.com/2) - ST2 is our favorite code editor. It takes some time to familiarize but once you get used to it, you'll have some hard time finding a replacement! The great thing with ST2 is that you can install or develop your own packages to improve your coding experience. Here after are some of theme :)
*	[ST2 Package Controler](http://wbond.net/sublime_packages/package_control) - First start with this one! It will allow you to manage and install great packages. Follow the instruction provided by the link and you'll be good to go!
*	[Arduino-like IDE](https://github.com/Robot-Will/Stino) - This package allow you to develop the Arduino code and upload it to your robot directly from within ST2. Everything is very well explained on their Github. If you are having some troubles, give us a call or contact them directly.
*	[Sublime - Arduino](https://github.com/theadamlt/Sublime-Arduino) - This package is really usefull because it provides syntax highlighting for Arduino code!


##Installing, Updating & Removing


###Hacker's guide

For you, it should be pretty easy.

Make sure you've installed the Arduino IDE.


####1. Installing `avr-gcc`, `binutils`, `avr-libc` and `avrdude`

We've made a Homebrew `formula` that you can `tap` like that:

	$ brew tap WeAreLeka/avr
	$ brew install avr-libc

Check that everything has been installed properly. If `avrdude` is missing, install it with:

	$ brew install avrdude


####2. Clone moti repository from Github

Simply clone the repo:

	$ cd path/to/wherever/you/want/to/clone/the/repo
	$ git clone https://github.com/WeAreLeka/moti.git
	$ cd moti
	$ git checkout dev

####3. Clone the Arduino-Makefile repo from Github

Simply clone the repo:

	$ cd path/to/wherever/you/want/to/clone/the/repo
	$ git clone https://github.com/WeAreLeka/Arduino-Makefile


####4. Install the perl dependencies needed to use the `makefile`

You need `YAML` and `Device::SerialPort` to upload with the `.hex` file. Simply type:

	$ sudo perl -MCPAN -e 'install +YAML'
	$ sudo perl -MCPAN -e 'install +Device::SerialPort'


####5. Symlinking the libraries

We've made some `shell scripts` to symlink all the libraries. In your Terminal, type:

	$ bash /path/to/moti/script/symlink_lib.sh


####6. Using the makefiles to compile your code

Take a look in `./src/moti_3`, you can see there is a Makefile. It looks like that:

	BOARD_TAG     = uno

	ARDMK_DIR     = ~/dev/arduino/arduino-makefile

	ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java

	AVR_TOOLS_DIR = /usr/local

	ARDUINO_PORT  = /dev/tty.usbmodemfa131

	PROJECT_DIR = /Users/Ladislas/dev/leka/moti

	CURRENT_DIR = $(shell basename $(CURDIR))

	include /Users/Ladislas/dev/arduino/arduino-makefile/arduino-mk/Arduino.mk

Everywhere your `.ino` files are, you want to put a makefile to compile the code. **Don't forget to configure it to suit your needs.**

Simply run `make` from `./src/moti_3` and it should compile. To upload, use `make upload`. For further information, visit [sudar's Arduin-Makefile repo](https://github.com/sudar/Arduino-Makefile).


###Beginner's guide - Installing from scratch on OS X/Unix


####Downloading and installing Sublime Text 2

Go visit the [Sublime Text 2 website](http://www.sublimetext.com/), download the package and install it as you would do with any other application.


####Downloading and installing the Arduino IDE

Go visit the [Arduino website](http://arduino.cc/en/Main/Software), download the package and install it as you would do with any other application.


####Downloading and installing a Git GUI

For comfort, we like like to use a Git GUI. For beginners, we recommend the Github Git GUI. Go visit the [Github for Mac website](http://mac.github.com/), download the package and install it as you would do with any other application.

For those on Linux or Windows, there are [apps](http://git-scm.com/downloads/guis) for you as well but we assume that if you are using Linux, you don't need one of them.


####Installing Homebrew

As we said earlier, Homebrew is a package manager. It's not a standard application with a graphical user interface (GUI). You have to open the Terminal.app to use Homebrew and type some command lines. If you're afraid, fear not my friend! We will guide you all along the way and you will eventually feel all the power of your computer!
If command line is really not your cup of tea, maybe you should just give up because we are going to use plenty of those later on! Come back when you're ready.

For those who want to fight, go visit the [Homebrew website](http://mxcl.github.io/homebrew/) and follow all the instructions. And because we are so generous, we also put them here: open Terminal.app, copy/paste the following line and let the magic begin (don't copy the `$` sign, it is used to say we are using the command line...):

	$ ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go)"

For troubleshooting, [Google](http://lmgtfy.com/?q=homebrew) is your best friend. You can also try typing `brew doctor` in your Terminal to see what is wrong. Please don't fill issues on Github regarding the installation of Homebrew, we won't read them.


####Installing Git with Homebrew

Now we are going to install/update Git with Homebrew.

Open the Terminal.app and then type:

	$ brew install git

And that's it! It will download the source and compile it. Everything should be OK.
Now you have the last Git version on your system which is pretty awesome you must say!


####Check Git version and amend `$PATH` if necessary

Now we're going to do a quick test to check that everything is up and running. In your terminal, type:

	$ git --version

And it should output something like that:

	$ git --version
	$ git version 1.8.3.1

If you have the 1.8.X version, it means that your are using the most recent version. If not, say you have 1.7.X, it "means" you are using the system version of Git because of a "path issue". But don't worry, we're going to fix this.

In your Terminal type:

	$ open /etc

The finder should open a new window to `/private/etc`, look for a file called `paths`. Right click on the file, choose `Open With` and choose Sublime Text 2 (if ST2 is not in the list, click Other... and look for it).

Sublime Text should open and display the content of `pahts`. It should look like this but it may vary:

	/usr/local/bin
	/usr/bin
	/usr/local/sbin
	/usr/bin
	/bin
	/sbin

Make sure that `/usr/local/bin` is before `/usr/bin`. In doubt you can copy and paste mine to replace yours and it will work fine.

Type `cmd+s` to save the file, you should be prompted to enter your password, so enter it, and voilà! You have just amended your `$PATH`, congratulations!

Quit (`cmd+q`) the Terminal.app, reopen the Terminal.app and type:

	$ git --version

To check your version. If it's not working, do the `$PATH` part again.


####Getting ready for the next part

**IMPORTANT: From here, things get a little more complex. If you follow up and take your time, everything should work fine. Please, before starting, read the whole procedure so you'll know where we are going.**

Remember that you installed the Arduino IDE, maybe you even started coding with it. We hope you didn't like it because, guess what! We're not going to use it! Yes, you've heard me, we think the Arduino IDE sucks (for now, it may become awesome one day, but we're waiting...) so we want to compile and upload everything on our own. Don't leave! It's not as complicated as it looks, plus some great minds have done most of the work for us! Ready? Let's get going! :)


####Installing avr-gcc and co

In this part, we are going to install `avr-gcc`, `binutils`, `avr-libc` and `avrdude`. To be brief, the three firt are used to compile your code for you Arduino microcontroller and the last one is used to upload the code on the Arduino.

To do this, we are going to use Homebrew, one more time! Type each of the following lines one by one:

	$ brew tap WeAreLeka/avr
	$ brew install avr-libc

This should install all you need. It may take some time to compile (up to one hour), so grab a coffee and a book and be patient. It is also normal, if you are using a laptop, to hear the fan. Compiling needs a lot of power.

Once it's done, you can check everything is fine by typing:

	$ avr-gcc -v
	$ avrdude -v

You should get something like that:

	$ avr-gcc -v
	Using built-in specs.
	... //	lots of stuff...
	Thread model: single
	gcc version 4.8.1 (GCC)

and

	$ avrdude -v
	avrdude: Version 5.11.1, compiled on Jun 20 2013 at 11:55:07
	...	// lots of stuff

If `avrdude` was not installed, you can do so by typing:

	$ brew install avrdude

And that's it! If something went wrong, fill an issue on Github using [this page](https://github.com/WeAreLeka/moti/issues).


####Cloning the moti repository from Github

If you just want to download the repo and use the code, get updates but don't contribute, you can clone the repo from Github. To do so, there are two ways :
*	first, you can use your favorite Git GUI and follow **their** instructions.
*	second, you can use the command line to feel like a boss.

For the second way, first, create a directory where you will clone all of our repos. We highly recommend to use something like that: `~/dev/leka` but anything should do, just write this path somewhere, we are going to use it.
Then, open the Terminal and type:

	$ cd path/to/wherever/you/want/to/clone/the/repo # e.g. cd ~/dev/leka
	$ git clone https://github.com/WeAreLeka/moti.git
	$ cd moti
	$ git checkout dev

You can also `git checkout master` but this branch may be a lot behind `dev`. However, changes in this branch are frequent and things might work one day but not the next day. If you can't fix, fill an issue.

So now, you have all the files needed for programming your own moti.


####Cloning the Arduino-makefile

As we said, we won't use the Arduino IDE, instead we are going to compile everything on our own. This is where things get interesting. To compile, you need a compiler. We do have one, remember, we installed `avr-gcc` earlier today. `avr-gcc` is derived from `gcc` a world famous compiler for C/C++ (our code will be written mostly in C/C++) and we will even use C++11, the last version of C++ which simplify a lot of things (we won't get into the details, but you can read all the documentation you need [here](http://en.wikipedia.org/wiki/C%2B%2B11) and [here](http://gcc.gnu.org/)). We could use pure command line to tell the computer how to compile the code using avr-gcc but as your code gets bigger, it becomes nearly impossible.

That's why some people invented the Makefiles. Makefiles are like a recipe for the computer which explains what to do with what and in which order. Writing a makefile on your own is like climbing Mont Everest with no training: it's impossible and you'll die alone and exhausted.

But here comes the open source community! Some great guys have written a working makefile for Arduino doing exactly what we intend to. You can thank [Sudar](http://hardwarefun.com/tutorials/compiling-arduino-sketches-using-makefile) and [Martin Oldfield](http://www.mjoldfield.com/atelier/2009/02/arduino-cli.html) and all the people who have contributed.

This makefile will be used as our reference, the one makefile to rule them all. We will also have smaller Makefiles later, we'll get to it.

We forked [Sudar's repo](https://github.com/sudar/Arduino-Makefile) to customize the makefile to our needs.

To clone the makefile, the process is quite the same: use your Git GUI or command line.

For the command line:

	$ cd path/to/wherever/you/want/to/clone/the/repo # e.g. cd ~/dev/leka
	$ git clone https://github.com/WeAreLeka/Arduino-Makefile
	$ cd Arduino-Makefile

By now, in your local project directory, you should have two directories: `moti` and `Arduino-Makefile`. If not, make sure you're looking at the right place...


####Let's use some Perl to get things up and running

The makefile we use is great, but on its own, it's not sufficient to upload the sketch and configure everything (say like knowing what kind of board you are using and finding its specs for the compiler). To do that, the same Sudar as before has written some perl scripts for us.

But we need to install some perl modules to get them working. Once again, it's quite easy! Open the Terminal and type line by line (you will be asked for you password because of `sudo`) :

	$ sudo perl -MCPAN -e 'install +YAML'
	$ sudo perl -MCPAN -e 'install +Device::SerialPort'

It may take some time and you may be asked questions, always answer `y` for "yes".


####Let's take a break, you earned it!

By now, things are pretty close to being up and running. We've done a lot of crazy things. It might look a little mysterious now, but as you get used to it, you'll finally understand why we did all that. Feel free to take looks into the different files, repos, folders and stuff we've done, ask Google about everything. You'll need to be a little aware of everything if you really want to enjoy our work.


####Let's take a look the moti directory tree

The moti directory tree looks like that:

	.
	|____lib
	| |____FreeSixIMU
	| |____Moti
	| |____RGBLED
	|____script
	|____sketch
	|____src
	| |____moti_1
	| |____moti_2
	| |____moti_3
	| | |____Makefile
	| | |____moti_3.ino
	|____test

Some explanations:

*	`lib` - all the libraries we use
*	`script` - three shell scripts we will use later to copy the libraries
*	`sketch` - the Fritzing sketches for moti, not up-to-date
*	`src` - the different version of moti, we are currently working on moti_3
*	`test` - unit tests

In `./src/moti_3`, you can see there is a Makefile. It looks like that:

	BOARD_TAG     = mega2560

	ARDMK_DIR     = ~/dev/arduino/arduino-makefile

	ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java

	AVR_TOOLS_DIR = /usr/local

	ARDUINO_PORT  = /dev/tty.usbmodemfa131

	PROJECT_DIR = /Users/Ladislas/dev/leka/moti

	CURRENT_DIR = $(shell basename $(CURDIR))

	include /Users/Ladislas/dev/arduino/arduino-makefile/arduino-mk/Arduino.mk

The Makefile is used to set some parameters for the compiler:

*	`BOARD_TAG` - the board you want to compile your code for (we will use uno or mega2560)
*	`ARDMK_DIR` - the path to the Arduino-Makefile directory, e.g. `~/dev/leka/Arduino-Makefile`
*	`ARDUINO_DIR` - the path to the important Arduino components used by the compiler (you can use `/Applications/Arduino.app/Contents/Resources/Java`)
*	`AVR_TOOLS_DIR` - path to `avr-gcc` and co, use `/usr/local`
*	`ARDUINO_PORT` - usb port where your arduino is connected. Connect your board to the computer, open the Arduino IDE, go to `Tools -> Serial Port` and look for the port starting with `/dev/tty.usbmodemXXXX` and replace `XXX` by your value.
*	`PROJECT_DIR` - the actual directory of moti
*	`CURRRENT_DIR` - the current directory of the makefile, do not touch
*	`include /path/to/Arduino-Makefile/arduino-mk/Arduino.mk` - use yours as above, it will include the `master Makefile`


####Install the libraries

To compile the code, you need the libraries we use. We wrote scripts that do that for you!

Open Terminal and type:

	$ cd path/to/moti
	$ cd script
	$ bash symlink_lib.sh

Then open a Finder windows and go to Documents/Arduino/libraries and check everything is in here.


####Use the makefile to make sure everything is up and running!

Now big time! We are **actually** going to compile our code, get ready!

Open Terminal and type:

	$ cd path/to/moti/src/moti_3
	make

The code should compile!




