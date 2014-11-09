# INSTRUCTIONS: copy and past the following inside your drone.io project setting.

# Environnement variables - must be copied in Drone.io
CWD=/home/ubuntu/src/github.com/WeAreLeka/moti
SRC=/home/ubuntu/src/github.com/WeAreLeka/moti/src
TEST=/home/ubuntu/src/github.com/WeAreLeka/moti/test
ARDMK=/home/ubuntu/src/github.com/WeAreLeka/moti/Arduino-Makefile

echo "Install avr-gcc..."
wget --quiet http://arduino.cc/download.php?f=/arduino-1.5.8-linux64.tgz
tar -xf arduino-1.5.8-linux64.tgz
sudo mv arduino-1.5.8/hardware/tools/avr/bin /usr/local/share/avr-gcc

echo "Install Arduino IDE..."
wget --quiet http://arduino.cc/download.php?f=/arduino-1.0.6-linux64.tgz
tar -xf arduino-1.0.6-linux64.tgz
sudo mv arduino-1.0.6/ /usr/local/share/arduino

echo "Cloning Arduino-Makefie and activate auto-lib..."
git submodule init && git submodule update
cd $ARDMK
git checkout auto-lib


echo "Test sources compilation..."
cd $SRC
for dir in *; do
	if [ -d "${dir}" ]; then
		echo "Trying to compile ${dir}..."
		cd $dir
		cp $CWD/Makefile-Drone.mk Makefile
		make
		echo "Building ${dir} passed with success!"
		cd ..
	fi
done

echo "Test tests compilation..."
cd $TEST
for dir in *; do
	if [ -d "${dir}" ]; then
		echo "Trying to compile ${dir}..."
		cd $dir
		cp $CWD/Makefile-Drone.mk Makefile
		make
		echo "Building ${dir} passed with success!"
		cd ..
	fi
done

