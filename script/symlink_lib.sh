#! /usr/bin/bash

SELFDIR=$PWD

PROJECTDIR=$(sed 's/\/script//g' <<< "$SELFDIR")

LIB_DIR=$PROJECTDIR/lib

ARDUINO_DEST_DIR=$HOME/Documents/Arduino/libraries

LIBS=$(ls $LIB_DIR)

for dir in $LIBS ;
do
	ln -s $LIB_DIR/$dir $ARDUINO_DEST_DIR;
done

echo "Installation successfull! Open the Arduino IDE and verify that the libraries are available."

