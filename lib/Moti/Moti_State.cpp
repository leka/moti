#include "Moti.h"
#include "Arduino.h"

//########//
// STATES //
//########//

bool Moti::isMoving(){
	return stateMoving;
}

bool Moti::isSleeping(){
	return stateSleeping;
}

bool Moti::isWaiting(){
	return stateWaiting;
}

bool Moti::isAwake(){
	return stateAwake;
}

bool Moti::isManipulated(){
	return stateManipulated;
}

bool Moti::isRemote(){
	return stateRemote;
}

void Moti::setMovingState(bool state){
	stateMoving = state;
}

void Moti::setSleepingState(bool state){
	stateSleeping = state;
}

void Moti::setWaitingState(bool state){
	stateWaiting = state;
}

void Moti::setAwakeState(bool state){
	stateAwake = state;
}

void Moti::setManipulatedState(bool state){
	stateManipulated = state;
}

void Moti::setRemoteState(bool state){
	stateRemote = state;
}
