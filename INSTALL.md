#Moti Installation Guide


##About

Here is the guide to correctly setup all you need to peacefully develop awesome code for Moti.

##Toolbox

###Basic

To help us develop our product, you'll first need to different softwares:

*	[Arduino IDE](http://arduino.cc/en/main/software) - this software is used to develop the source code and to upload it to your Arduino board. We recommend going for the 1.0.5 version. If you are a little more advanced user feel free to try the new beta version 1.5. Please note that you may encounter strange behaviors (we do sometimes), so please, take the time to report them in the [Due Forum](http://forum.arduino.cc/index.php?board=87.0) and/or here.
*	[Homebrew](http://mxcl.github.io/homebrew/) - Homebrew is our best package manager for OS X (a Linux version is under development). Homebrew helps you download and install packages to do whatever your need to do, without compromising your computer and the weird stuff going on in `/usr/local/`
*	[Git](http://git-scm.com/) - Of course, you need to have git install but we assume that if you are reading this, you know what it is and how to use it. If you're not really comfortable with the Terminal, you can use a Git GUI. [Try this list](http://git-scm.com/download/gui/mac), test them and stick to the one you prefer! :)
*	[Github account](https://github.com/signup/free) - Sign up for free, fork the project, improve the awesomeness and pull it back!

With these softwares, you should be up and running and ready to hack autism with Moti!


###Advanced

Okay, so you started with the Arduino and Processing IDE, you're now familiarized with the languages, you've already read and write something like a thousand lines of code and you would really love some new tools to speed up your coding and improve your coding experience. Here are some solutions for you that we, at Leka, are using on a daily basis with great pleasure!

*	[Sublime Text 2](http://www.sublimetext.com/2) - ST2 is our favorite code editor. It takes some time to familiarize but once you get used to it, you'll have some hard time finding a replacement! The great thing with ST2 is that you can install or develop your own packages to improve your coding experience. Here after are some of theme :)
*	[ST2 Package Controler](http://wbond.net/sublime_packages/package_control) - First start with this one! It will allow you to manage and install great packages. Follow the instruction provided by the link and your good to go!
*	[Arduino-like IDE](https://github.com/Robot-Will/Stino) - This package allow you to develop the Arduino code and upload it to your robot directly from within ST2. Everything is very well explained on their Github. If you are having some troubles, give us a call or contact them directly.
*	[Sublime - Arduino](https://github.com/theadamlt/Sublime-Arduino) - This package is really usefull because it provides syntax highlighting for Arduino code!


##Installing, Updating & Removing

###Installing from scratch on OS X/Unix (beginner guide)

####Downloading and installing Sublime Text 2

Go visit the [Sublime Text 2 website](http://www.sublimetext.com/), download the package and install it as you would do with any other application.

####Downloading and installing the Arduino IDE

Go visit the [Arduino website](http://arduino.cc/en/Main/Software), download the package and install it as you would do with any other application.

####Downloading and installing a Git GUI

For comfort, we like like to use a Git GUI. For beginners, we recommend the Github Git GUI. Go visit the [Github for Mac website](http://mac.github.com/), download the package and install it as you would do with any other application.

For those on Linux or Windows, there [apps](http://git-scm.com/downloads/guis) for you as well but we're assuming that if you are using Linux, you don't need one of them.

####Installing Homebrew

As we said earlier, Homebrew is a package manager. It's not a standard application with a graphical user interface (GUI). You have to open the Terminal.app to use Homebrew and type some command lines. If you're afraid, fear not my friend! We will guide you all along the way and you will eventually feel all the power of your computer!
If command line is really not your cup of tea, maybe you should just give up because we are going to use plenty of those later on! Come back when you're ready.


For those who want to fight, go visit the [Homebrew website](http://mxcl.github.io/homebrew/) and follow all the instructions. And because we are so generous, we put them here: open Terminal.app, copy/paste the following line and let the magic begin (don't copy the `$` sign, it is used to say we are using the command line...):

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

One it's done, you can check everything is fine by typing:

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

And that's it! If something went wrong, fill and issue on Github using [this page](https://github.com/WeAreLeka/moti/issues).


Note: Make sure Git and cURL are installed.

For the project, we use different libraries. Some of them are public, well-known libraries from the Arduino website and some are custom made to suit our needs.
If you want to be able to compile the project, you need to have our libraries inside your library folder so they can be accessed by the Arduino app.
[By following this link](http://arduino.cc/en/Guide/Libraries), you'll know here to find yours depending on your OS: Windows or a UNIX based system (OS X, Linux, Debian, etc.)

###Stable on Linux/Unix based systems using make install

####Installing

The following instructions should work on Mac OS X, Debian, Ubuntu, etc. (We haven't tested it yet, if you do, contact us!)

The easiest way is to use Git and make for installing:

	$ git clone https://github.com/WeAreLeka/moti.git
	$ cd YOUR/PATH/TO/moti/
	$ git checkout dev # or master for working versions
	$ make install

Basically it just makes symlinks from ./lib to ./Arduino/libraries. Make sure you don't already have a library with the same name, it can cause troubles. Plus, we may have made some changes to the libraries, so it's better to use our versions.


####Updating

Updating using git:

	$ git pull
	$ make update

Use update when new libraries are added.


##How to use

"Okay, I've cloned the repo, installed all the softwares, but I'm quite new to Arduino and I don't know what to do!" - That's all right! You might not be a geek like us, but you will be sooner than you think.

Here are some things to do for your robot to start living :

1.	Visit our [Bill of Material page](sketch/README.md) and buy the different parts from your favorite retailer.
1.	Wait a couple of days for the mailman.
1.	Build the robot, yeah!
1.	Connect the Arduino board to your computer using the usb cable.
1.	Open the Arduino IDE or ST2.
1.	Open the project.
1.	Go to src/moti_1 or src/moti_2 (depending on the robot you're building) and open moti_1.ino or moti_2.ino (or any version we might be developing in the future!).
1.	Upload the sketch to the Arduino board. The way of doing this will depend on the software you're using. We advise you to read the necessary documentation.
1.	Enjoy! :)


##Known Issues

###Moti 2 - v1.0

*	none yet (we're so cool!)

###Moti 1 - v0.1

*	the speed and the light depend on the excitement of the robot, but when the motors are running, moti is exciting itself perpetually... need to change that!


##Uninstalling

###Linux/Unix based OS

To remove all the libraries used for the Moti project, simply run:

	$ git pull
	$ make uninstall

The uninstaller is clever! You don't need to worry about your own libraries being removed, only our libraries are targeted and removed.


