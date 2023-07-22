#include <float.h>
#include "lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int **create_int_mat(int size, bool randomize, int limit, int shift)
{
    if(size<1) {
    size = 1;
    }
    int **matrix = (int **)malloc(sizeof(int *) * (unsigned)size);
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * (unsigned)size);
        for (int j = 0; j < size; j++) {
            if (randomize) {
                matrix[i][j] = generate_random_int_value(limit, shift);
            } else {
                matrix[i][j] = 0; // Initialization of a matrix with zeros
            }
        }
    }
    return matrix;
}

double **create_double_mat(int size, bool randomize, int limit, int shift)
{
    if(size<2) {
    size = 2;
    }
    double **matrix = (double **)malloc(sizeof(double *) * (unsigned)size);
    for (int i = 0; i < size; i++) {
        matrix[i] = (double *)malloc(sizeof(double) * (unsigned)size);
        for (int j = 0; j < size; j++) {
            if (randomize) {
                matrix[i][j] = generate_random_double_value(limit, shift);
            } else {
                matrix[i][j] = 0; // Initialization of a matrix with zeros
            }
        }
    }
    return matrix;
}

int generate_random_int_value(int limit, int shift) {
    int rand_val;
    int random_value;
    if (limit > 0) {
        rand_val = (int)rand() % limit;
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        rand_val = -((int)rand() % -limit);
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        rand_val = (int)rand();
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

double generate_random_double_value(double limit, double shift) {
    double rand_val;
    double random_value;
    if (limit > 0) {
        rand_val = (double)rand() / RAND_MAX * limit;
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        rand_val = -((double)rand() / RAND_MAX * -limit);
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        rand_val = (double)rand() / RAND_MAX;
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
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

void destroy_int_mat(int **matrix, int size)
{
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void destroy_double_mat(double **matrix, int size)
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

double *diagonal(double **mat_in,double *arr,int size){
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

void print_int_mat(int **mat_in, int rows, int cols) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(j==0){
                printf("[\t");
            }
            printf("%d\t", mat_in[i][j]);
            if(j==cols-1){
                printf("]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_double_mat(double **mat_in, int rows, int cols) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(j==0){
                printf("[\t");
            }
            printf("%.2f\t", mat_in[i][j]);
            if(j==cols-1){
                printf("]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool adj_reverse_mat(double **mat_in, double **mat_out, int size) {
    // Calculate the determinant of the input matrix
    double det = get_determinant(mat_in, size);
    // If the determinant is zero, the inverse matrix does not exist
    if (det == 0) {
        return false;
    }
    // Calculate the adjugate matrix
    double **adj = create_double_mat(size, false, 0, 0);
    get_adj_matrix(mat_in, adj, size);

    // Calculate the inverse matrix
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat_out[i][j] = adj[i][j] / det;

    // Free memory
    destroy_double_mat(adj, size);
    return true;
}

double get_determinant(double **mat, int size) {
    double det = 0;
    // If the matrix size is 1, the determinant is equal to the only element of the matrix
    if (size == 1) {
        return mat[0][0];
    } else if (size == 2) {
        // If the matrix size is 2, use the formula to calculate the determinant
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    } else {
        // Otherwise use a recursive approach
        for (int col = 0; col < size; col++) {
            // Create a submatrix of size size-1 x size-1
            double **sub_mat = create_double_mat(size - 1, false, 0, 0);
            for (int sub_i = 1; sub_i < size; sub_i++) {
                int sub_j = 0;
                for (int j = 0; j < size; j++) {
                    if (j == col)
                        continue;
                    sub_mat[sub_i - 1][sub_j] = mat[sub_i][j];
                    sub_j++;
                }
            }
            // Calculate the determinant of the submatrix and add it to the total determinant
            det += (col % 2 == 0 ? 1 : -1) * mat[0][col] * get_determinant(sub_mat, size - 1);
            // Free memory
            destroy_double_mat(sub_mat, size - 1);
        }
    }
    return det;
}


void get_cofactor(double **mat, double **temp, int p, int q, int size) {
    int i = 0, j = 0;
    // Iterate over all elements of the matrix
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // Skip elements from row p and column q
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void get_adj_matrix(double **mat, double **adj, int size) {
    // If the matrix size is 1, the adjugate matrix consists of a single element equal to 1
    if (size == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    // Create a temporary matrix to store cofactors
    double **temp = create_double_mat(size,false,0,0);

    // Iterate over all elements of the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Calculate the cofactor for the current element
             get_cofactor(mat, temp, i, j, size);
            // Calculate the sign for the current element
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            // Calculate the determinant of the cofactor and store it in the adjugate matrix
            adj[j][i] = sign * get_determinant(temp, size - 1);
            
        }
    }
    // Free memory
    destroy_double_mat(temp,size);
}