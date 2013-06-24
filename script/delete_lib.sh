#! /usr/bin/bash

SELFDIR=$PWD

PROJECTDIR=$(sed 's/\/script//g' <<< "$SELFDIR")

LIB_DIR=$PROJECTDIR/lib

ARDUINO_DEST_DIR=$HOME/Documents/Arduino/libraries

LIBS=$(ls $LIB_DIR)

for dir in $LIBS ;
do
	rm -rf $ARDUINO_DEST_DIR/$dir;
done

echo "Everything has been cleaned up, you can proceed with your life..."