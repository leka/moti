/*
 * UdpString.cpp: Library to send/receive UDP packets with the Arduino ethernet shield
 * using Tom Igoe/Hernando Barragan's WString library.
 * Drop UdpString.h/.cpp from this distribution into the Ethernet library directory at 
 * hardware/libraries/Ethernet/ 
 * Then copy directory /libraries/String from this distribution to /hardware/libraries/String in
 * your Arduino installation.
 *
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * bjoern@cs.stanford.edu 12/30/2008
 */

extern "C" {
#include "types.h"
#include "w5100.h"
#include "socket.h"
}

#include "Ethernet.h"
#include "UdpString.h"

/* Start UDP socket, listening at local port PORT */
void UdpStringClass::begin(uint16_t port) {
	_port = port;
	_sock = 0; //TODO: should not be hardcoded
	socket(_sock,Sn_MR_UDP,_port,0);
}

/* Is data available in rx buffer? Returns 0 if no, number of available bytes if yes. */
int UdpStringClass::available() {
	return getSn_RX_RSR(_sock);
}

/////////////////////////////////////////
//Wstring functions
int UdpStringClass::sendPacket(String str, byte * ip, unsigned int port) {
	return (int)sendto(_sock,(const uint8_t *)str.cstr(),str.length(),ip,port);
}

int UdpStringClass::sendPacket(String str, int length, byte * ip, unsigned int port) {
	return (int)sendto(_sock,(const uint8_t *)str.cstr(),length,ip,port);
}

int UdpStringClass::readPacket(String &str) {
	uint8_t ip[4];
	uint16_t port[1];
	return readPacket(str,ip,port);
}

/* read packet into String str - if str is too short, expand its capacity */
int UdpStringClass::readPacket(String &str, byte * ip, unsigned int *port) {
	int len = available() -8; //skip UDP header
	if(len <= 0) return 0;
	if(len > str.capacity()) {
		//packet is longer than string capacity - 
		//resize string - this is very implementation dependent on WString
		str = String(len);		
		//fall through to read which should be ok now
	}
	return (int)recvfrom(_sock,(byte *)(str.cstr()),(uint16_t)str.capacity(),ip,port);
}

/* Create one global object */
UdpStringClass UdpString;
