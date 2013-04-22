#! /usr/bin/make -f
SHELL=/bin/sh

SELFDIR?=${CURDIR}

DESTDIR?=~/Documents/Arduino/libraries/

install:
	ln -s $(SELFDIR)/lib/* $(DESTDIR)
	
	@echo "Installation successfull! Open the Arduino IDE and verify that the libraries are available."

clean:
	rm -rf $(DESTDIR)/*
	
	@echo "Everything has been cleaned up, you can proceed with your life..."

cleaninstall: clean install
