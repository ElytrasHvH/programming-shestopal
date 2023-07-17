/**
 * @file lib.c
 * @brief Реалізація функцій для обчислення квадратної матриці та функції НСД.
 */
#include "lib.h"

int **SquareMat(int **mat_in, int **mat_out, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				// Perform multiplication and accumulate the result
				mat_out[i][j] += mat_in[i][k] * mat_in[k][j];
			}
		}
	}

	return mat_out;
}

int gcd(int num1, int num2)
{
	int frstnum = num1;
	int scndnum = num2;

	// Handling negative numbers
	if (frstnum < 0) {
		frstnum = -frstnum; // GCD for negative numbers is the same as for positive, so we invert it
	}
	if (scndnum < 0) {
		scndnum = -scndnum;
	}

	// Base cases
	if (scndnum == 0 || scndnum == 1 || frstnum == scndnum) {
		return frstnum;
	}
	if (frstnum == 0 || frstnum == 1) {
		return scndnum;
	}

	// Computing GCD using the Euclidean algorithm
	while (frstnum != scndnum) {
		if (frstnum > scndnum) {
			frstnum -= scndnum;
		} else {
			scndnum -= frstnum;
		}
	}

	return frstnum;
}
