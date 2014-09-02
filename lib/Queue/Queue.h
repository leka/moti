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

#define QUEUE_MAX_SIZE 256

template<typename T>
class Queue {
	public:
		Queue(void);
		~Queue(void);

		void push();
		T pop(void);
		T getHead(void);

		bool isEmpty(void);

		void fill(uint16_t i, T item);
		T get(void);

		T getTail(void);

	private:
		uint16_t _current, _nItems;
		T _items[QUEUE_MAX_SIZE];
};



template<typename T>
Queue<T>::Queue(void) {
	_current = _nItems = 0;
}


template<typename T>
Queue<T>::~Queue(void) {
	_current = _nItems = 0;
}

template<typename T>
void Queue<T>::push(void) {
	// _items[(_current + _nItems) % QUEUE_MAX_SIZE] = item;

	if (_nItems + 1 < QUEUE_MAX_SIZE)
		++_nItems;
}

template<typename T>
T Queue<T>::pop(void) {
	T head = _items[_current];

	if (_nItems == 1)
		_current = 0;
	else
		++_current;

	--_nItems;

	return head;
}

template<typename T>
T Queue<T>::getHead(void) {
	return _items[_current];
}

template<typename T>
bool Queue<T>::isEmpty(void) {
	return _nItems == 0;
}

template<typename T>
void Queue<T>::fill(uint16_t i, T item) {
	if (i < QUEUE_MAX_SIZE)
		_items[i] = item;
}

template<typename T>
T Queue<T>::getTail(void) {
	return _items[(_current + _nItems) % QUEUE_MAX_SIZE];
}

#endif
