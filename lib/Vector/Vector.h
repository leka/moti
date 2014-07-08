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

#ifndef LEKA_MOTI_ARDUINO_VECTOR_H_
#define LEKA_MOTI_ARDUINO_VECTOR_H_

/**
 * @file Vector.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

 #include <Arduino.h>


template<class T> class Vector {
	public:
		Vector() {
			Vector(1);
		}

		Vector(uint16_t size) {
			_size = size;
			_length = 0;

			Serial.println("Vector created");

			_data = (T*)malloc(_size * sizeof(T));
		}

		~Vector() {
			free(_data);
		}

		void push(T e) {
			if (_size == _length) {
				_size <<= 1;
				_data = (T*)realloc(_data, _size * sizeof(T));
			}

			_data[_length++] = e;
		}


		T pop(uint16_t i) {
			T e = _data[i];

			for (uint16_t j = i + 1; j < _length; j++)
				_data[j - 1] = _data[j];

			_length--;

			return e;
		}

		inline T& operator[](uint16_t i) { return _data[i]; }

		uint16_t length() { return _length; }

	private:
		uint16_t _size, _length;
		T* _data;
};

#endif
