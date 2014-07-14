/*

#include "Vector.h"

template<class T>
Vector<T>::Vector() {
	Vector(1);
}

template<class T>
Vector<T>::Vector(uint16_t size) {
	_size = size;
	_length = 0;

	_data = (T*)malloc(_size * sizeof(T));
}

template<class T>
Vector<T>::~Vector() {
	free(_data);
}

template<class T>
void Vector<T>::push(T e) {
	if (_size == _length) {
		_size << 1;
		_data = (T*)realloc(_data, _size * sizeof(T));
	}

	_data[_length++] = e;
}

template<class T>
T Vector<T>::pop(uint16_t i) {
	T e = _data[i];

	for (uint16_t j = i + 1; j < _length; j++)
		_data[j - 1] = _data[j];

	_length--;

	return e;
}

*/