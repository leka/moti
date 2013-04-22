# test_udp_throughput.py
# measure throughput of a2d messages using arduino_osc_udp firmware
# requires simpleOSC 0.2 from www.ixi-software.net
# this test enables a2d reporting on all pins 
# and counts how many messages arrive per second

# output will look like this
# 1000 : 1000 msgs in 2.3476 sec [ 425.96 Hz]
# 2000 : 1000 msgs in 2.0576 sec [ 485.99 Hz]
# 3000 : 1000 msgs in 2.0080 sec [ 498.02 Hz]
# 4000 : 1000 msgs in 1.9991 sec [ 500.21 Hz]
# ...
# NOTE: 
# by default, the firmware reports each channel at 100Hz, and only sends messages when values change
# so reasonable values are 400-600 messages/second.
# 
# We can measure a hard maximum of how many messages arduino_osc_udp can send
# by editing the firmware and setting a2dReportFrequency = 0
# and by removing the check  if(result!=a2dBuffer[channel]) {...} in checkAnalogInput()
# when reporting on all 6 channels, we get:
# 1000 : 1000 msgs in 0.5305 sec [ 1885.14 Hz]
# 2000 : 1000 msgs in 0.5285 sec [ 1892.00 Hz]
# 3000 : 1000 msgs in 0.5287 sec [ 1891.56 Hz]
# 4000 : 1000 msgs in 0.5286 sec [ 1891.80 Hz]
# ...
# if we enable just a single adc channel, we can test how fast our main loop is
# (checking discrete inputs, checking one adc channel, checking for incoming messages):
# 6000 : 1000 msgs in 1.0226 sec [ 977.87 Hz]
# 7000 : 1000 msgs in 1.0245 sec [ 976.07 Hz]
# 8000 : 1000 msgs in 1.0196 sec [ 980.77 Hz]
# 9000 : 1000 msgs in 1.0239 sec [ 976.62 Hz]

# Upshot: we can read a single channel at ~975Hz, 
# and have a total maximum throughput of ~1890 adc messages/sec

import osc
import time
numMsgs = 0; #how many msgs we've received
startTime=time.time()

def myTest():
	osc.init()
	osc.listen('192.168.11.15', 8000) #local IP; listen on port 8000
	osc.bind(recvMsg,"/adc/5")
	#osc.bind(recvMsg,"/adc/1")
	#osc.bind(recvMsg,"/adc/2")
	#osc.bind(recvMsg,"/adc/3")
	#osc.bind(recvMsg,"/adc/4")
	#osc.bind(recvMsg,"/adc/5")
	# enable reporting of all adc channels
	osc.sendMsg("/report/adc/5",[1],'192.168.11.200',8888) # Arduino's IP and Port
	while 1:
		time.sleep(0.1)
	
def recvMsg(*msg):
	global numMsgs,startTime
	numMsgs=numMsgs+1
	if (numMsgs%1000)==0:
		elapsed = time.time() - startTime
		print numMsgs, ": 1000 msgs in %1.4f sec [ %3.2f Hz]" % (elapsed,(1000/elapsed))
		startTime = time.time()
	
if __name__ == '__main__': myTest()