#include "Moti.h"
#include "Arduino.h"

//########//
// STATES //
//########//

void MOTI::initializeStates(){
	setMovingState(false);
	setSleepingState(false);
	setWaitingState(true);
	setAwakeState(true);
	setManipulatedState(false);
	setRemoteState(false);
}

bool MOTI::isMoving(){
	return _stateMoving;
}

bool MOTI::isSleeping(){
	return _stateSleeping;
}

bool MOTI::isWaiting(){
	return _stateWaiting;
}

bool MOTI::isAwake(){
	return _stateAwake;
}

bool MOTI::isManipulated(){
	return _stateManipulated;
}

bool MOTI::isRemote(){
	return _stateRemote;
}

void MOTI::setMovingState(bool state){
	_stateMoving = state;
}

void MOTI::setSleepingState(bool state){
	_stateSleeping = state;
}

void MOTI::setWaitingState(bool state){
	_stateWaiting = state;
}

void MOTI::setAwakeState(bool state){
	_stateAwake = state;
}

void MOTI::setManipulatedState(bool state){
	_stateManipulated = state;
}

void MOTI::setRemoteState(bool state){
	_stateRemote = state;
}
