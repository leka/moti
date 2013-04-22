/*
 * UdpBytewise.cpp: Library to send/receive UDP packets with the Arduino ethernet shield.
 * Drop UdpBytewise.h/.cpp into the Ethernet library directory at hardware/libraries/Ethernet
 *
 * NOTE: UDP is fast, but has some important limitations (thanks to Warren Gray for mentioning these)
 * 1) UDP does not guarantee the order in which assembled UDP packets are received. This
 * might not happen often in practice, but in larger network topologies, a UDP
 * packet can be received out of sequence. 
 * 2) UDP does not guard against lost packets - so packets *can* disappear without the sender being
 * aware of it. Again, this may not be a concern in practice on small local networks.
 * For more information, see http://www.cafeaulait.org/course/week12/35.html
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

#ifndef UdpBytewise_h
#define UdpBytewise_h

#include "Print.h"

#define UDP_TX_PACKET_MAX_SIZE 32
#define UDP_RX_PACKET_MAX_SIZE 32

#define UDP_TX_OVERFLOW_TRUNCATE 0
#define UDP_TX_OVERFLOW_SPLIT 1

class UdpBytewiseClass: public Print {
private:
	uint8_t _sock;  // socket ID for Wiz5100
	uint16_t _port; // local port to listen on
	
	uint8_t _txBuffer[UDP_TX_PACKET_MAX_SIZE];
	uint8_t _txIndex;
	uint8_t _txIp[4];
	uint16_t _txPort;
	uint8_t _txOverflowStrategy; 
	
	uint8_t _rxBuffer[UDP_RX_PACKET_MAX_SIZE];
	uint8_t _rxIndex;
	int _rxSize;
	uint8_t _rxIp[4];
	uint16_t _rxPort;
	
public:
	void begin(uint16_t);				// initialize, start listening on specified port
	int available();				    // has data been received?

	// Single byte-oriented functions:
	int beginPacket(uint8_t *ip, unsigned int port); // returns 1 on success, 0 if we already started a packet
	virtual void write(uint8_t); // add a byte to the currently assembled packet (if there's space)
	int endPacket(); // returns # of bytes sent on success, 0 if there's nothing to send
	
	int read(); //read a byte if available - returns -1 if no data available
	
	void getSenderIp(uint8_t * ip);  //get remote IP of the packet we're currently reading from
	unsigned int getSenderPort();  //get remote port# of the packet we're currently reading from
	void setOverflowStrategy(uint8_t); // what to do when our packet is full and we try to add more?
};

extern UdpBytewiseClass UdpBytewise;
#endif
