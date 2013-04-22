/*
 * UdpBytewise.cpp: Library to send/receive UDP packets with the Arduino ethernet shield.
 * Drop UdpBytewise.h/.cpp into the Ethernet library directory at hardware/libraries/Ethernet/ 
 * TODO: should protect buffer access with critical sections
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
#include "UdpBytewise.h"

/* Start UDP socket, listening at local port PORT */
void UdpBytewiseClass::begin(uint16_t port) {
	_port = port;
	_sock = 0; //TODO: should not be hardcoded
	_txIndex =0;
	_rxIndex =0;
	_rxSize = 0;
	_txOverflowStrategy = UDP_TX_OVERFLOW_SPLIT;	
	socket(_sock,Sn_MR_UDP,_port,0);
}


/* Is data available in rx buffer? Returns 0 if no, number of available bytes if yes. */
int UdpBytewiseClass::available() {
	if(_rxSize==0 || _rxSize-_rxIndex==0) { 
		//if local buffer is empty or depleted
		//check wiz5100 buffer for new packet
		_rxSize = getSn_RX_RSR(_sock); //note: return value is inflated by 8 byte header
		if(_rxSize){
			//if we have a new packet there
			//reset buffer index
			_rxIndex=0;
			//copy packet into our local buffer
			_rxSize = recvfrom(_sock,_rxBuffer,_rxSize-8,_rxIp,&_rxPort);
		} else {
			//else do nothing and rxsize is still 0
			;
		}
		return _rxSize; //return the new number of bytes in our buffer
	} else{
		//if buffer is not empty, return remaining # of bytes
		return (_rxSize-_rxIndex);
	}
}


/* Start a new packet with given target ip and port 
 * returns 1 on success, 0 if we already started a packet */
int UdpBytewiseClass::beginPacket(uint8_t *ip, unsigned int port) {	
	if(_txIndex==0) {
		//ok to start new packet - copy ip and port
		_txIp[0]=ip[0];
		_txIp[1]=ip[1];
		_txIp[2]=ip[2];
		_txIp[3]=ip[3];
		_txPort = port;
		return 1;
	}
	else {
		//we already started a packet and have data in it
		return 0;
	}
}


/* Add a byte to the currently assembled packet if there is space
 * if there isn't space, either truncate (ignore) or split the packet.
 */
void UdpBytewiseClass::write(uint8_t b) {
	if(_txIndex>= UDP_TX_PACKET_MAX_SIZE) {
		//buffer is full - we can either truncate the packet or split in two
		switch (_txOverflowStrategy) {
			case UDP_TX_OVERFLOW_SPLIT:
				endPacket();
				beginPacket(_txIp,_txPort);
				//fall through to normal add of byte to buffer below
				break;
			case UDP_TX_OVERFLOW_TRUNCATE:
			default:
				//don't add - just ignore bytes past buffer size
				return;
		}
	}
	_txBuffer[_txIndex++] = b;
}

/* send an assembled packet out 
 * returns # of bytes sent on success, 0 if there's nothing to send */
int UdpBytewiseClass::endPacket() {
	// send the packet
	uint16_t result = sendto(_sock,(const uint8_t *)_txBuffer,_txIndex,_txIp,_txPort);
	// reset buffer index
	_txIndex=0;
	// return sent bytes
	return (int)result;
}

/* read the next byte of the last rececived packet */
int UdpBytewiseClass::read() {
	if(_rxIndex < _rxSize) {
		// if there is something to be read, return the next byte
		return _rxBuffer[_rxIndex++];		
	} else {
		//we already sent the last byte - nothing to do
		return -1;
	}
}
	
void UdpBytewiseClass::getSenderIp(uint8_t*ip) {
	ip[0]=_rxIp[0];
	ip[1]=_rxIp[1];
	ip[2]=_rxIp[2];
	ip[3]=_rxIp[3];
}
	
unsigned int  UdpBytewiseClass::getSenderPort() {
	return _rxPort;
}

/* what should we do when we try to add to a full outgoing packet? 
 * UDP_TX_OVERFLOW_TRUNCATE - throw overflow bytes away
 * UDP_TX_OVERFLOW_SPLIT - split into multiple packets
 */
void UdpBytewiseClass::setOverflowStrategy(uint8_t strategy) {
	_txOverflowStrategy = strategy;
}

/* Create one global object */
UdpBytewiseClass UdpBytewise;
