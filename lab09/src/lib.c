/**
 * @file lib.c
 * @brief Реалізація функцій для обчислення квадратної матриці та функції НСД.
 */
#include "lib.h"

int **SquareMat(int **MatIn, int **MatOut, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int s = 0; s < size; s++) {
				// Perform multiplication and accumulate the result
				MatOut[i][j] += MatIn[i][s] * MatIn[s][j];
			}
		}
	}

	return MatOut;
}

int gcd(int x, int y)
{
	int x1 = x;
	int y1 = y;

	// Handling negative numbers
	if (x1 < 0) {
		x1 = -x1; // GCD for negative numbers is the same as for positive, so we invert it
	}
	if (y1 < 0) {
		y1 = -y1;
	}

	// Base cases
	if (y1 == 0 || y1 == 1 || x1 == y1) {
		return x1;
	}
	if (x1 == 0 || x1 == 1) {
		return y1;
	}

	// Computing GCD using the Euclidean algorithm
	while (x1 != y1) {
		if (x1 > y1) {
			x1 -= y1;
		} else {
			y1 -= x1;
		}
	}

	return x1;
}
