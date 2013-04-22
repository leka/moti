# test_udp_latency.py
# measure latency using echo messages

# sends 10 echoes back and forth and measures elapsed time
# pauses in between echo bursts to let all buffers drain on Arduino

# output looks like this on my home network:
# 10 : 10 echos in 0.0750 sec  - avg. roundtrip is 7.5041 millis
# 20 : 10 echos in 0.0232 sec  - avg. roundtrip is 2.3167 millis
# 30 : 10 echos in 0.0209 sec  - avg. roundtrip is 2.0939 millis
# 40 : 10 echos in 0.0250 sec  - avg. roundtrip is 2.4983 millis

# NOTE: after a few thousand messages,  everything grinds to a halt
# maybe because some buffer gets flooded? unsure...


import osc
import time
numMsgs = 0; #how many msgs we've received
startTime=time.time()

def myTest():
	osc.init()
	osc.listen('192.168.11.15', 8000) #local IP; listen on port 8000
	osc.bind(recvMsg,"/echo")
	# enable reporting of all adc channels
	osc.sendMsg("/echo",[0],'192.168.11.200',8888) # Arduino's IP and Port
	while 1:
		time.sleep(0.1)
	
def recvMsg(*msg):
	global numMsgs,startTime
	numMsgs=numMsgs+1
	if (numMsgs%10)==0:
		elapsed = time.time() - startTime
		print numMsgs, ": 10 echos in %1.4f sec  - avg. roundtrip is %1.4f millis" % (elapsed,elapsed*100)
		time.sleep(1)
		startTime = time.time()
	osc.sendMsg("/echo",[0],'192.168.11.200',8888) # Arduino's IP and Port
if __name__ == '__main__': myTest()