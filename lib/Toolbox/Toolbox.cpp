#include "Toolbox.h"

float Toolbox::mod(float a, float b) {
	float m = (float)fmod((double)a, (double)b);

	if (m < 0.f) {
		m += b;
	}

	return m;
}

float Toolbox::diffAngle(float a, float b) {
	float diff = a - b;

	return mod(diff + 180.f, 360.f) - 180.f;
}

float Toolbox::arrayDeltaSum(float* array, uint8_t size) {
	float sum = abs(diffAngle(array[0], array[size - 1]));

	for (uint8_t i = 1; i < size; ++i)
		sum += abs(diffAngle(array[i], array[i - 1]));

	return sum;
}


