
#include <stdlib.h>
#include <time.h>

int **create_mat(int size, int randomize, int limit, int shift)
{
	srand((unsigned int)time(NULL));
	int **matrix = (int **)malloc(sizeof(int *) * (unsigned)size);
	for (int i = 0; i < size; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * (unsigned)size);
		for (int j = 0; j < size; j++) {
			if (randomize) {
				int random_value = (int)random() % limit + shift; // Random value generation with limit and shift
				matrix[i][j] = random_value;
			} else {
				matrix[i][j] = 0; // Initialization of a matrix with zeros
			}
		}
	}
	return matrix;
}

void destroy_mat(int **matrix, int size)
{
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void square_mat(int **mat_in, int **mat_out, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat_out[i][j] = 0; // Initialize the output matrix to 0
			for (int k = 0; k < size; k++) {
				// Perform multiplication and accumulate the result
				mat_out[i][j] += mat_in[i][k] * mat_in[k][j];
			}
		}
	}
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
