#include "Moti.h"
#include "Arduino.h"

//########//
// STATES //
//########//

bool Moti::isMoving(){
	return _stateMoving;
}

bool Moti::isSleeping(){
	return _stateSleeping;
}

bool Moti::isWaiting(){
	return _stateWaiting;
}

bool Moti::isAwake(){
	return _stateAwake;
}

bool Moti::isManipulated(){
	return _stateManipulated;
}

bool Moti::isRemote(){
	return _stateRemote;
}

void Moti::setMovingState(bool state){
	_stateMoving = state;
}

void Moti::setSleepingState(bool state){
	_stateSleeping = state;
}

void Moti::setWaitingState(bool state){
	_stateWaiting = state;
}

void Moti::setAwakeState(bool state){
	_stateAwake = state;
}

void Moti::setManipulatedState(bool state){
	_stateManipulated = state;
}

void Moti::setRemoteState(bool state){
	_stateRemote = state;
}
