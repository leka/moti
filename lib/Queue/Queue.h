/*
Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

This file is part of Moti, a spherical robotic smart toy for autistic children.

Moti is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Moti is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Moti. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LEKA_MOTI_ARDUINO_QUEUE_H
#define LEKA_MOTI_ARDUINO_QUEUE_H

#include <Arduino.h>

/**
 * @file Queue.h
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */


template<typename T>
class Queue {
	public:
		Queue();
		~Queue();

		void push(T item);
		T pop();
		T getHead();

		bool isEmpty();

	private:

		typedef struct element {
			T item;
			element* next;
		} element;

		element *head, *tail;

		uint16_t size;
};



template<typename T>
Queue<T>::Queue() {
    head = tail = NULL;
    size = 0;
}


template<typename T>
Queue<T>::~Queue() {
    element* current = head;

    while (head != NULL) {
        current = current->next;
        delete head;
        head = current;
    }

    tail = NULL;
    size = 0;
}

template<typename T>
void Queue<T>::push (T item) {
    element* oldTail = tail;

    tail = (element*) new element;

    if (tail == NULL) {
        Serial.println(F("Cannot create Queue element"));
        return;
    }

    tail->next = NULL;
    tail->item = item;

    if (isEmpty())
        head = tail;
    else
        oldTail->next = tail;
    
    ++size;
}

template<typename T>
T Queue<T>::pop () {
    if (isEmpty())
        Serial.println(F("Pop empty queue..."));

    T item = head->item;
    element* newHead = head->next;

    delete head;
    head = newHead;

    --size;

    return item;
}

template<typename T>
T Queue<T>::getHead() {
    if (isEmpty())
        Serial.println(F("Head empty queue..."));

    return head->item;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return size == 0;
}

#endif
