#! /usr/bin/make

SHELL=/bin/sh

SELFDIR?=${CURDIR}

ARDU_DIR?=${SELFDIR}/lib/arduino

ARDU_DEST_DIR?=${HOME}/Documents/Arduino/libraries

ARDU_LIB = $(shell ls $(ARDU_DIR))

all:
	@echo "usage: make install     ->     installs arduino's lib"	
	@echo "       make uninstall   ->     uninstalls arduino's libs"
	@echo "       make update      ->     updates if new libraries added"

install-arduino:
	@for dir in $(ARDU_LIB) ; \
	do \
		(ln -s ${ARDU_DIR}/$$dir $(ARDU_DEST_DIR)/); \
	done

install: install-arduino
	@echo "Installation successfull! Open the Arduino IDE and verify that the libraries are available."

clean-arduino:
	@for dir in $(ARDU_LIB) ; \
	do \
		(rm -rf ${ARDU_DEST_DIR}/$$dir); \
	done

uninstall: clean-arduino
	@echo "Everything has been cleaned up, you can proceed with your life..."

update: uninstall install
	@echo "Everything has been updated, enjoy the new awesomeness!"
