#include "lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int **create_mat(int size, bool randomize, int limit, int shift)
{
    if(size<2) {
    size = 2;
    }
    int **matrix = (int **)malloc(sizeof(int *) * (unsigned)size);
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * (unsigned)size);
        for (int j = 0; j < size; j++) {
            if (randomize) {
                matrix[i][j] = generate_random_value(limit, shift);
            } else {
                matrix[i][j] = 0; // Initialization of a matrix with zeros
            }
        }
    }
    return matrix;
}
int generate_random_value(int limit, int shift) {
    int rand_val;
    int random_value;
    if (limit > 0) {
        rand_val = (int)random() % limit;
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        rand_val = -((int)random() % -limit);
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        rand_val = (int)random();
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Only shifts values if limit is not given
        }
    }
    return random_value;
}

int *create_arr(int size)
{
    if(size<1)
    {
        return NULL;
    }
    int* arr=(int* )malloc(sizeof(int)*(unsigned)size);
    return arr;
}

void destroy_arr(int* arr)
{
    free(arr);
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

int *diagonal(int **mat_in,int *arr,int size){
    for(int i = 0; i<size; i++)
    {
        *(arr + i) = *(*(mat_in + i) + i); //why...
    }
    return arr;
}

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
