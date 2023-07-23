#include "lib.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

double **create_double_mat(int size, bool randomize, double limit, double shift)
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

double generate_random_double_value(double limit, double shift) {
    double rand_val;
    double random_value;
    if (limit > 0) {
        rand_val = (double)random() / RAND_MAX * limit;
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        rand_val = -((double)random() / RAND_MAX * -limit);
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        rand_val = (double)random() / RAND_MAX;
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


int *create_int_arr(int size)
{
    if(size<1)
    {
        return NULL;
    }
    int* arr=(int* )malloc(sizeof(int)*(unsigned)size);
    for(int i=0;i<size;i++) {
	arr[i]=0;
    }    
    return arr;
}

double *create_double_arr(int size)
{
    if(size<1)
    {
        return NULL;
    }
    double* arr=(double* )malloc(sizeof(double)*(unsigned)size);
    for(int i=0;i<size;i++) {
	arr[i]=0;
	}
    return arr;
}

void destroy_arr(void* arr)
{
    free(arr);
}

void destroy_mat(void **matrix, int size)
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
    if (fabs(det) < 1e-9) {
        return false;
    }
    // Calculate the adjugate matrix
    double **adj = create_double_mat(size, false, 0, 0);
    get_adj_matrix(mat_in, adj, size);

    // Calculate the inverse matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat_out[i][j] = adj[i][j] / det;
		}
	}
    // Free memory
    destroy_mat((void**)adj, size);
    return true;
}

double get_determinant(double **mat, int size) {
    double det = 1;
    double **mat_clone = create_double_mat(size, false, 0, 0);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            mat_clone[row][col] = mat[row][col];
        }
    }
    for (int index = 0; index < size; index++) {
        int max_index = index;
        for (int j = index + 1; j < size; j++) {
            if (fabs(mat_clone[j][index]) > fabs(mat_clone[max_index][index])) {
                max_index = j;
            }
        }
        if (fabs(mat_clone[max_index][index]) < 1e-9) {
            destroy_mat((void**)mat_clone, size);
            return 0;
        }
        swap_rows((void**)mat_clone, index, max_index);
        if (index != max_index) {
            det = -det;
        }
        det *= mat_clone[index][index];
        for (int j = index + 1; j < size; j++) {
            mat_clone[index][j] /= mat_clone[index][index];
        }
        for (int j = 0; j < size; j++) {
            if (j != index && fabs(mat_clone[j][index]) > 1e-9) {
                for (int k = index + 1; k < size; k++) {
                    mat_clone[j][k] -= mat_clone[index][k] * mat_clone[j][index];
                }
            }
        }
    }
    destroy_mat((void**)mat_clone, size);
    return det;
}

void get_cofactor(double **mat, double **temp, int p_index, int q_index, int size) {
    int i_index = 0;
    int j_index = 0;
    // Iterate over all elements of the matrix
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // Skip elements from row p and column q
            if (row != p_index && col != q_index) {
                temp[i_index][j_index++] = mat[row][col];
                if (j_index == size - 1) {
                    j_index = 0;
                    i_index++;
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
    destroy_mat((void**)temp,size);
}

void swap_rows(void **mat, int row1, int row2) {
    void *temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}
