#! /usr/bin/make

SHELL=/bin/sh

SELFDIR?=${CURDIR}

PROC_DIR?=${SELFDIR}/lib/processing
ARDU_DIR?=${SELFDIR}/lib/arduino

PROC_DEST_DIR?=${HOME}/Documents/Processing/libraries
ARDU_DEST_DIR?=${HOME}/Documents/Arduino/libraries

PROC_LIB = $(shell ls $(PROC_DIR))
ARDU_LIB = $(shell ls $(ARDU_DIR))

all:
	@echo "usage: make install-arduino     -> installs arduino's lib only"
	@echo "       make install-processing     -> installs processing's lib only"
	@echo "       make install	-> installs arduino and processing libs"	
	@echo "       make uninstall -> uninstalls arduino and processing libs"
	@echo "       make clean-arduino"
	@echo "       make clean-processing"

install-arduino:
	@for dir in $(ARDU_LIB) ; \
	do \
		(ln -s ${ARDU_DIR}/$$dir $(ARDU_DEST_DIR)/); \
	done

install-processing:
	@for dir in $(PROC_LIB) ; \
	do \
		(ln -s ${PROC_DIR}/$$dir $(PROC_DEST_DIR)/); \
	done

install: install-arduino install-processing
	@echo "Installation successfull! Open the Arduino & Processing IDE and verify that the libraries are available."

clean-arduino:
	@for dir in $(ARDU_LIB) ; \
	do \
		(rm -rf ${ARDU_DEST_DIR}/$$dir); \
	done

clean-processing:
	@for dir in $(PROC_LIB) ; \
	do \
		(rm -rf ${PROC_DEST_DIR}/$$dir); \
	done

uninstall: clean-arduino clean-processing	
	@echo "Everything has been cleaned up, you can proceed with your life..."

update: uninstall install
