
#include "lib.h"
#include <ctype.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#define random() rand()
#define srandom(seed) srand(seed)
#endif

#ifndef HAVE_STRLCPY
// Implement the strlcpy function only if it's not already defined.
size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t src_len = 0;
    while (src[src_len] != '\0' && src_len + 1 < size) {
        dst[src_len] = src[src_len];
        src_len++;
    }

    if (size > 0) {
        dst[src_len] = '\0';
    }

    while (src[src_len] != '\0') {
        src_len++;
    }

    return src_len;
}
#endif
// Function to create a 2D integer matrix of given size
// with an option to randomize the values within a given range.
// Parameters:
//   - size: The size of the square matrix to be created.
//   - randomize: A boolean flag indicating whether to randomize the matrix values.
//   - limit: The upper limit for random values if randomize is true.
//   - shift: The shift value for random values if randomize is true.
// Returns:
//   - A pointer to the 2D integer matrix.
int **create_int_mat(size_t size, bool randomize, int limit, int shift) {
	
	// If the size is less than 1, set it to 1 to ensure a valid matrix.
	if (size < 1) {
		size = 1;
	}
	
	// Allocate memory for an array of size "size" to store pointers to integer arrays.
	int **matrix = (int **)malloc(sizeof(int *) * size);

	// Iterate over the rows of the matrix and allocate memory for each row.
	for (size_t i = 0; i < size; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * size);

		// Iterate over the columns of the matrix.
		for (size_t j = 0; j < size; j++) {
			
			// If randomize is true, generate a random integer value within the given range.
			if (randomize) {
				matrix[i][j] = generate_random_int_value(limit, shift);
			} else {
				// If randomize is false, set the matrix element to 0.
				matrix[i][j] = 0; 
			}
		}
	}
	
	// Return the pointer to the created matrix.
	return matrix;
}
// Function to create a 2D double precision floating-point matrix of given size
// with an option to randomize the values within a given range.
// Parameters:
//   - size: The size of the square matrix to be created.
//   - randomize: A boolean flag indicating whether to randomize the matrix values.
//   - limit: The upper limit for random values if randomize is true.
//   - shift: The shift value for random values if randomize is true.
// Returns:
//   - A pointer to the 2D double precision floating-point matrix.
double **create_double_mat(size_t size, bool randomize, double limit, double shift) {
	
	// If the size is less than 1, set it to 1 to ensure a valid matrix.
	if (size < 1) {
		size = 1;
	}
	
	// Allocate memory for an array of size "size" to store pointers to double precision floating-point arrays.
	double **matrix = (double **)malloc(sizeof(double *) * size);

	// Iterate over the rows of the matrix and allocate memory for each row.
	for (size_t i = 0; i < size; i++) {
		matrix[i] = (double *)malloc(sizeof(double) * size);

		// Iterate over the columns of the matrix.
		for (size_t j = 0; j < size; j++) {
			
			// If randomize is true, generate a random double precision floating-point value within the given range.
			if (randomize) {
				matrix[i][j] = generate_random_double_value(limit, shift);
			} else {
				// If randomize is false, set the matrix element to 0.
				matrix[i][j] = 0.0; 
			}
		}
	}
	
	// Return the pointer to the created matrix.
	return matrix;
}
// Function to create a dynamic integer array of the given size and initialize all elements to 0.
// Parameters:
//   - size: The size of the integer array to be created.
// Returns:
//   - A pointer to the dynamically allocated integer array.
//   - Returns NULL if the provided size is less than 1 (invalid size).
int *create_int_arr(size_t size) {
	
	// If the size is less than 1, return NULL to indicate an error (invalid size).
	if (size < 1) {
		return NULL;
	}
	
	// Allocate memory for an array of integers of size "size".
	int* arr = (int *)malloc(sizeof(int) * size);
	if (arr==NULL){
		return NULL;
	}
	// Initialize all elements of the array to 0.
	for (size_t i = 0; i < size; i++) {
		arr[i] = 0;
	}
	
	// Return the pointer to the dynamically allocated integer array.
	return arr;
}
// Function to create a dynamic array of double precision floating-point numbers of the given size.
// All elements of the array are initialized to 0.
// Parameters:
//   - size: The size of the double precision floating-point array to be created.
// Returns:
//   - A pointer to the dynamically allocated double precision floating-point array.
//   - Returns NULL if the provided size is less than 1 (invalid size) or if memory allocation fails.
double *create_double_arr(size_t size) {
	
	// If the size is less than 1, return NULL to indicate an error (invalid size).
	if (size < 1) {
		return NULL;
	}
	
	// Allocate memory for an array of double precision floating-point numbers of size "size".
	double* arr = (double *)malloc(sizeof(double) * size);

	// Check if memory allocation was successful.
	// If memory allocation fails, return NULL to indicate an error.
	if (arr == NULL) {
		return NULL;
	}
	
	// Initialize all elements of the array to 0.
	for (size_t i = 0; i < size; i++) {
		arr[i] = 0.0;
	}
	
	// Return the pointer to the dynamically allocated double precision floating-point array.
	return arr;
}
// Function to create a dynamic array of characters (char) of the given size.
// Parameters:
//   - size: The size of the character array to be created.
// Returns:
//   - A pointer to the dynamically allocated character array.
//   - Returns NULL if memory allocation fails.
char *create_char_arr(size_t size) {
	// Initialize a character pointer to NULL.
	char* char_arr = NULL;

	// Attempt to allocate memory for a character array of size "size".
	char_arr = (char *)malloc(sizeof(char) * size);

	// If memory allocation fails, return NULL to indicate an error.
	if (char_arr == NULL) {
		return NULL;
	}

	// Return the pointer to the dynamically allocated character array.
	return char_arr;
}


// Function to create a dynamic string (char array) of the given size with all elements initialized to null characters '\0'.
// Parameters:
//   - size: The size of the string (character array) to be created.
// Returns:
//   - A pointer to the dynamically allocated string (character array).
//   - Returns NULL if memory allocation fails.
char *create_string(size_t size) {
	// Create a character array (string) using the create_char_arr function.
	char* string = create_char_arr(size + 1);

	// Check if memory allocation was successful.
	// If memory allocation fails, return NULL to indicate an error.
	if (string == NULL) {
		return NULL;
	}

	// Initialize all elements of the string (character array) to null characters '\0'.
	memset(string, 0, size + 1);

	// Return the pointer to the dynamically allocated string (character array).
	return string;
}


// Function to free the memory allocated for a dynamic array (generic pointer).
// Parameters:
//   - arr: A pointer to the dynamically allocated array to be freed.
void destroy_arr(void* arr) {
	// Free the memory associated with the array.
	free(arr);
}


// Function to free the memory allocated for a dynamic 2D array (matrix) of void pointers.
// Parameters:
//   - matrix: A pointer to the 2D array (matrix) of void pointers to be freed.
//   - size: The size of the square matrix (number of rows) to be freed.
void destroy_mat(void **matrix, size_t size) {
	// Iterate over the rows of the matrix.
	for (size_t i = 0; i < size; i++) {
		// Free the memory associated with each row (1D array) of the matrix.
		free(matrix[i]);
	}
	// Free the memory associated with the array of row pointers (matrix).
	free(matrix);
}
// Function to increase the capacity of a dynamic array by doubling its current capacity.
// Parameters:
//   - arr: A pointer to the dynamic array (double pointer) whose capacity is to be increased.
//   - capacity: A pointer to the current capacity of the array. It will be updated after the increase.
void increase_capacity(double **arr, size_t *capacity) {
	// Double the current capacity.
	*capacity *= 2;
	
	// Attempt to reallocate memory for the array with the new capacity.
	double *temp = (double *)realloc(*arr, *capacity * sizeof(double));
	
	// If memory reallocation fails, print an error message, free the old array, and exit the program with failure status.
	if (temp == NULL) {
		(void)fprintf(stderr, "Memory reallocation error for the array.\n");
		free(*arr);
		exit(EXIT_FAILURE);
	}
	
	// Update the pointer to the array to point to the newly allocated memory.
	*arr = temp;
}
// Function to generate a random integer value within a given range and shift.
// Parameters:
//   - limit: The upper or lower limit (positive or negative) for the random value.
//   - shift: The shift value to be added to the random value.
// Returns:
//   - A random integer value within the specified range and shift.

int generate_random_int_value(int limit, int shift) {
	
	// Declare variables to store the intermediate and final random values.
	int rand_val;
	int random_value;
	
	// If the limit is positive, generate a random value in the range [0, limit - 1].
	if (limit > 0) {
		rand_val = (int)random() % limit;
		
		// If the shift is positive and the generated value is close to INT_MAX, set the random value to INT_MAX.
		if (shift > 0 && rand_val > INT_MAX - shift) {
			random_value = INT_MAX; 
		}
		// If the shift is negative and the generated value is close to INT_MIN, set the random value to INT_MIN.
		else if (shift < 0 && rand_val < INT_MIN - shift) {
			random_value = INT_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	// If the limit is negative, generate a random value in the range [limit + 1, 0].
	else if (limit < 0) {
		rand_val = -((int)random() % -limit);
		
		// If the shift is positive and the generated value is close to INT_MAX, set the random value to INT_MAX.
		if (shift > 0 && rand_val > INT_MAX - shift) {
			random_value = INT_MAX; 
		}
		// If the shift is negative and the generated value is close to INT_MIN, set the random value to INT_MIN.
		else if (shift < 0 && rand_val < INT_MIN - shift) {
			random_value = INT_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	// If the limit is zero, generate a random value in the range [0, INT_MAX].
	// In this case, the shift determines whether the value can be negative or positive.
	else {
		rand_val = (int)random();
		
		// If the shift is positive and the generated value is close to INT_MAX, set the random value to INT_MAX.
		if (shift > 0 && rand_val > INT_MAX - shift) {
			random_value = INT_MAX; 
		}
		// If the shift is negative and the generated value is close to INT_MIN, set the random value to INT_MIN.
		else if (shift < 0 && rand_val < INT_MIN - shift) {
			random_value = INT_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	
	// Return the final random value.
	return random_value;
}
// Function to generate a random double precision floating-point value within a given range and shift.
// Parameters:
//   - limit: The upper or lower limit (positive or negative) for the random value.
//   - shift: The shift value to be added to the random value.
// Returns:
//   - A random double precision floating-point value within the specified range and shift.

double generate_random_double_value(double limit, double shift) {
	
	// Declare variables to store the intermediate and final random values.
	double rand_val;
	double random_value;
	
	// If the limit is positive, generate a random value in the range [0, limit].
	if (limit > 0) {
		// Generate a random double precision floating-point value in the range [0, 1].
		// The random() function generates random integer values in the range [0, RAND_MAX].
		// To get a random value in the range [0, 1], divide by RAND_MAX.
		// Scale the value by the specified limit to get the random value within the range [0, limit].
		rand_val = (double)random() / RAND_MAX * limit;
		
		// If the shift is positive and the generated value is close to DBL_MAX, set the random value to DBL_MAX.
		if (shift > 0 && rand_val > DBL_MAX - shift) {
			random_value = DBL_MAX; 
		}
		// If the shift is negative and the generated value is close to DBL_MIN, set the random value to DBL_MIN.
		else if (shift < 0 && rand_val < DBL_MIN - shift) {
			random_value = DBL_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	// If the limit is negative, generate a random value in the range [limit, 0].
	else if (limit < 0) {
		// Generate a random double precision floating-point value in the range [0, 1].
		// The random() function generates random integer values in the range [0, RAND_MAX].
		// To get a random value in the range [0, 1], divide by RAND_MAX.
		// Scale the value by the absolute value of the specified limit to get the random value within the range [0, -limit].
		rand_val = -((double)random() / RAND_MAX * -limit);
		
		// If the shift is positive and the generated value is close to DBL_MAX, set the random value to DBL_MAX.
		if (shift > 0 && rand_val > DBL_MAX - shift) {
			random_value = DBL_MAX; 
		}
		// If the shift is negative and the generated value is close to DBL_MIN, set the random value to DBL_MIN.
		else if (shift < 0 && rand_val < DBL_MIN - shift) {
			random_value = DBL_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	// If the limit is zero, generate a random value in the range [0, 1].
	// In this case, the shift determines whether the value can be negative or positive.
	else {
		// Generate a random double precision floating-point value in the range [0, 1].
		// The random() function generates random integer values in the range [0, RAND_MAX].
		// To get a random value in the range [0, 1], divide by RAND_MAX.
		rand_val = (double)random() / RAND_MAX;
		
		// If the shift is positive and the generated value is close to DBL_MAX, set the random value to DBL_MAX.
		if (shift > 0 && rand_val > DBL_MAX - shift) {
			random_value = DBL_MAX; 
		}
		// If the shift is negative and the generated value is close to DBL_MIN, set the random value to DBL_MIN.
		else if (shift < 0 && rand_val < DBL_MIN - shift) {
			random_value = DBL_MIN; 
		}
		// Otherwise, apply the shift to the random value to get the final random value.
		else {
			random_value = rand_val + shift; 
		}
	}
	
	// Return the final random value.
	return random_value;
}
// Function to perform bubble sort on an integer array in ascending order.
// Parameters:
//   - arr: A pointer to the integer array to be sorted.
//   - size: The number of elements in the array.
void bubble_sort(int *arr, int size) {
	// Perform the bubble sort algorithm on the array.
	// The outer loop runs from the first element to the second-to-last element.
	// The inner loop runs from the first element to the (size - i - 2) element, where i is the index of the outer loop.
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			// Compare adjacent elements in the array.
			// If the current element is greater than the next element, swap them.
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}


// Function to compute the square matrix multiplication of two square integer matrices.
// Parameters:
//   - mat_in: A pointer to the input square matrix (2D integer array).
//   - mat_out: A pointer to the output square matrix (2D integer array) that stores the result.
//   - size: The size of the square matrices (number of rows and columns).
void square_mat(int **mat_in, int **mat_out, int size) {
	// Perform matrix multiplication of the input square matrix mat_in with itself and store the result in mat_out.
	// The outer loops iterate over each row and column of the output matrix mat_out.
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Initialize the element at the current row and column in mat_out to 0.
			mat_out[i][j] = 0; 
			
			// The inner loop iterates over each element in the row i of mat_in and the column j of mat_in,
			// and performs the summation required for matrix multiplication.
			for (int k = 0; k < size; k++) {
				mat_out[i][j] += mat_in[i][k] * mat_in[k][j];
			}
		}
	}
}
// Function to extract the diagonal elements of a square matrix and store them in an array.
// Parameters:
//   - mat_in: A pointer to the input square matrix (2D double array).
//   - arr: A pointer to the output array that stores the diagonal elements.
//   - size: The size of the square matrix (number of rows and columns).
// Returns:
//   - A pointer to the array containing the diagonal elements of the matrix.

double *diagonal(double **mat_in, double *arr, int size) {
	// Iterate over the diagonal elements of the square matrix.
	for (int i = 0; i < size; i++) {
		// Extract the value of the diagonal element at position (i, i) and store it in the output array.
		// The expression *(*(mat_in + i) + i) accesses the element at row i and column i in the 2D array mat_in.
		// The value of the diagonal element is assigned to the corresponding position in the output array.
		*(arr + i) = *(*(mat_in + i) + i);
	}
	// Return a pointer to the array containing the diagonal elements.
	return arr;
}


// Function to compute the adjugate (adjoint) matrix of a square matrix and store it in another matrix.
// Parameters:
//   - mat_in: A pointer to the input square matrix (2D double array).
//   - mat_out: A pointer to the output square matrix (2D double array) that stores the adjugate matrix.
//   - size: The size of the square matrices (number of rows and columns).
// Returns:
//   - A boolean value indicating whether the computation was successful.
//     If the determinant of the input matrix is close to zero, the function returns false.

bool adj_reverse_mat(double **mat_in, double **mat_out, size_t size) {
	// Compute the determinant of the input matrix.
	double det = get_determinant(mat_in, size);
	
	// Check if the determinant is close to zero.
	if (fabs(det) < 1e-7) {
		// If the determinant is zero, the inverse matrix does not exist (but since fp's sucks we can't use ==; rip all matrix who has determinant < 1e-9 or > -1e-9).
		// Return false to indicate that the computation was not successful.
		return false;
	}
	
	// Create a temporary matrix to store the adjugate matrix.
	double **adj = create_double_mat(size, false, 0, 0);
	
	// Compute the adjugate matrix of the input matrix and store it in the temporary matrix adj.
	get_adj_matrix(mat_in, adj, size);

	// Perform scalar division to obtain the inverse matrix.
	// Divide each element of the adjugate matrix by the determinant of the input matrix.
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			mat_out[i][j] = adj[i][j] / det;
		}
	}

	// Free the memory allocated for the temporary matrix adj.
	destroy_mat((void**)adj, size);
	
	// Return true to indicate that the computation was successful and the inverse matrix is obtained.
	return true;
}

// Function to perform LU decomposition with partial pivoting
// This function takes the input matrix `mat`, its `size` (number of rows/columns),
// and performs LU decomposition with partial pivoting. LU decomposition
// represents the matrix as the product of a lower triangular matrix (L)
// and an upper triangular matrix (U). It also keeps track of row swaps using `pivot` array.
void lu_decomposition(double** mat, size_t size, double** lu_matrix,int* pivot) {
    // Initialize LU matrix with the input matrix (copying data)
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            lu_matrix[i][j] = mat[i][j];
        }
    }

    // Initialize pivot array
    for (size_t i = 0; i < size; i++) {
        pivot[i] = (int)i;
    }

    // Perform LU decomposition
    for (size_t i = 0; i < size; i++) {
        // Find the row with the maximum absolute value in the current column (i).
        size_t max_index = i;
        for (size_t j = i + 1; j < size; j++) {
            if (fabs(lu_matrix[j][i]) > fabs(lu_matrix[max_index][i])) {
                max_index = j;
            }
        }

        // Swap the rows to move the pivot element to the current row (i).
        if (max_index != i) {
            for (size_t j = 0; j < size; j++) {
                double temp = lu_matrix[i][j];
                lu_matrix[i][j] = lu_matrix[max_index][j];
                lu_matrix[max_index][j] = temp;
            }

            // Update the pivot array to keep track of row swaps.
            int temp_pivot = pivot[i];
            pivot[i] = pivot[max_index];
            pivot[max_index] = temp_pivot;
        }

        // Eliminate the non-zero elements below the pivot element in the current column.
        for (size_t j = i + 1; j < size; j++) {
            lu_matrix[j][i] /= lu_matrix[i][i];
            for (size_t k = i + 1; k < size; k++) {
                lu_matrix[j][k] -= lu_matrix[j][i] * lu_matrix[i][k];
            }
        }
    }
}


// Function to compute the determinant from LU decomposition
// This function takes the LU matrix obtained from `lu_decomposition`,
// its `size` (number of rows/columns), and `pivot` array to adjust the sign of the determinant
// based on the number of row swaps performed during LU decomposition.
// The determinant is computed as the product of diagonal elements of LU matrix.
double determinant_from_lu(double** lu_matrix, size_t size,const int* pivot)  {
    double det = 1.0;
    for (size_t i = 0; i < size; i++) {
        det *= lu_matrix[i][i];
    }

    // Adjust the sign of the determinant based on the number of row swaps
    int sign = 1;
    for (size_t i = 0; i < size; i++) {
        if ((const int)i != pivot[i]) {
            sign *= -1;
        }
    }

    return det * sign;
}

// Function to get the determinant of the matrix
// This is the main function to get the determinant of the input matrix `mat`.
// It uses LU decomposition with partial pivoting to compute the determinant
// without modifying the original matrix.
// The function first creates a temporary matrix `mat_clone` to hold a copy of `mat`.
// Then it creates LU matrix and `pivot` array for LU decomposition.
// The LU decomposition is performed, and the determinant is computed using `determinant_from_lu`.
// Finally, the temporary matrices are freed, and the determinant is returned.
double get_determinant(double** mat, size_t size) {
    // Create a temporary matrix mat_clone for LU decomposition
    double **mat_clone = create_double_mat(size, false, 0, 0);
    for (size_t row = 0; row < size; row++) {
        for (size_t col = 0; col < size; col++) {
            mat_clone[row][col] = mat[row][col];
        }
    }

    // Create LU matrix and pivot array for LU decomposition
    double **lu_matrix = create_double_mat(size, false, 0, 0);
    int *pivot = create_int_arr(size);

    // Perform LU decomposition
    lu_decomposition(mat, size, lu_matrix, pivot);

    // Compute determinant from LU decomposition
    double det = determinant_from_lu(lu_matrix, size, (const int*)pivot);

    // Free allocated memory
    destroy_mat((void**)mat_clone, size);
    destroy_mat((void**)lu_matrix, size);
    free(pivot);

    return det;
}

// Function to compute the cofactor matrix of a given element in a square matrix.
// The cofactor matrix is obtained by removing the row and column containing the specified element.
// Parameters:
//   - mat: A pointer to the input square matrix (2D double array).
//   - temp: A pointer to the output square matrix (2D double array) that stores the cofactor matrix.
//   - p_index: The row index of the element for which the cofactor matrix is computed.
//   - q_index: The column index of the element for which the cofactor matrix is computed.
//   - size: The size of the square matrices (number of rows and columns).
void get_cofactor(double **mat, double **temp, size_t p_index, size_t q_index, size_t size) {
    // Initialize the indices for the temporary matrix temp.
    size_t i_index = 0;
    size_t j_index = 0;

    // Iterate over each element of the input matrix mat to compute the cofactor matrix.
    for (size_t row = 0; row < size; row++) {
        // Skip the row containing the element at (p_index, q_index).
        if (row == p_index) {
            continue;
        }

        // Pointers to the current row of the input matrix mat and the corresponding row of the temporary matrix temp.
        double *src_row = mat[row];
        double *dest_row = temp[i_index];

        for (size_t col = 0; col < size; col++) {
            // Skip the column containing the element at (p_index, q_index).
            if (col == q_index) {
                continue;
            }

            // Store the value of the current element in the corresponding position of the temporary matrix temp.
            dest_row[j_index++] = src_row[col];

            // If j_index reaches the last column of the temporary matrix, reset it to zero and increment i_index.
            if (j_index == size - 1) {
                j_index = 0;
                i_index++;
            }
        }
    }
}
// Function to compute the adjugate (adjoint) matrix of a square matrix.
// The adjugate matrix is the transpose of the cofactor matrix of the input matrix.
// Parameters:
//   - mat: A pointer to the input square matrix (2D double array).
//   - adj: A pointer to the output square matrix (2D double array) that stores the adjugate matrix.
//   - size: The size of the square matrices (number of rows and columns).
void get_adj_matrix(double **mat, double **adj, size_t size) {
	// If the size of the matrix is 1, set the adjugate matrix to be the identity matrix.
	if (size == 1) {
		adj[0][0] = 1;
		return;
	}

	// Variable to determine the sign of the elements in the adjugate matrix.
	int sign = 1;

	// Create a temporary matrix temp to hold the cofactor matrix of each element.
	double **temp = create_double_mat(size, false, 0, 0);

	// Iterate over each element of the input matrix mat to compute the adjugate matrix.
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			// Compute the cofactor matrix of the element at position (i, j) and store it in the temporary matrix temp.
			get_cofactor(mat, temp, i, j, size);
			
			// Determine the sign of the element in the adjugate matrix based on the position (i, j).
			sign = ((i + j) % 2 == 0) ? 1 : -1;
			
			// Calculate the element in the adjugate matrix by multiplying the determinant of the cofactor matrix with the sign.
			adj[j][i] = sign * get_determinant(temp, size - 1);
		}
	}

	// Free the memory allocated for the temporary matrix temp.
	destroy_mat((void**)temp, size);
}
// Function to swap two rows in a 2D matrix (array of pointers to rows).
// Parameters:
//   - mat: A pointer to the 2D matrix (array of pointers to rows).
//   - row1: The index of the first row to be swapped.
//   - row2: The index of the second row to be swapped.
void swap_rows(void **mat, size_t row1, size_t row2) {
	// Temporary pointer to store the address of the first row.
	void *temp = mat[row1];
	
	// Swap the addresses of the first and second rows in the matrix.
	mat[row1] = mat[row2];
	mat[row2] = temp;
}

double **convert_array_to_mat(const double *arr, size_t count, size_t *size) {
    (*size) = (size_t)get_int_square_root((int)count);
	double** mat_out = create_double_mat(*size,0,0,0);
    for (size_t i = 0; i < *size; i++) {
		for(size_t j = 0; j < *size; j++){
			mat_out[i][j]=arr[(*size)*i+j];
		}
    }
    return mat_out;
}

// Function to skip leading whitespace characters in a C-style string and return a pointer to the first non-whitespace character.
// Parameters:
//   - str: A pointer to the input C-style string (null-terminated character array).
// Returns:
//   - A pointer to the first non-whitespace character in the string.
const char* skip_whitespace(const char* str) {
	// Loop through the string until a non-whitespace character is encountered.
	while (isspace(*str)) {
		str++;
	}
	// Return a pointer to the first non-whitespace character or the null terminator if the string contains only whitespace.
	return str;
}

// Function to clear the input stream (stdin) up to the next newline character or the end of file (EOF).
// This function is useful for clearing the input buffer after reading a value from stdin to avoid unwanted characters interfering with future input.
// Parameters:
//   - stream: A pointer to the input stream to be cleared (e.g., stdin).
void clear_input_stream(FILE *stream) {
    int clear;
    // Loop through the input stream until a newline character or EOF is encountered.
    // This effectively clears the input buffer up to the next line or end of file.
    while ((clear = fgetc(stream)) != '\n' && clear != EOF) {
        // Do nothing; the loop discards the characters read from the input stream.
    }
}

// Function to read a line of input from stdin and store it in a dynamically allocated string.
// The function reads characters until a newline character or the end of file (EOF) is encountered.
// Parameters:
//   - length: A pointer to a size_t variable to store the length of the read string (output parameter).
//   - filled: A pointer to a boolean variable that indicates whether the input was successfully read (output parameter).
// Returns:
//   - A dynamically allocated char array (string) containing the read input.
//   - If the end of file (EOF) is encountered before reading any characters, returns NULL.
char* read_input() {
	// Define the buffer size for reading from stdin.
	const size_t buffer_size = 8096;

	// Create a temporary buffer and a string to store the read input.
	size_t temp_length = 0;
	char* buffer = create_char_arr(buffer_size);
	char* str = create_string(buffer_size);



	// Read a line of input (up to buffer_size characters) from stdin into the buffer.
	if (fgets(buffer, buffer_size, stdin) == NULL) {
		clear_input_stream(stdin);
		// If end of file (EOF) is encountered before reading any characters, return NULL.
		free(buffer);
		free(str);
		return NULL;
	}

	// Clear any remaining characters in the input buffer up to the next newline character or EOF.
	clear_input_stream(stdin);

	// Calculate the length of the read string in the temporary buffer.
	while (buffer[temp_length] != '\0' && buffer[temp_length] != '\n') {
		temp_length++;
	}

	// If the length is 0 then nothing was copied 
	if (temp_length == 0) {
		free(buffer);
		free(str);
		return NULL;
	}

	// Copy the contents of the temporary buffer to the dynamically allocated string using memcpy.
	memcpy(str, buffer, buffer_size);

	// Free the temporary buffer and return the dynamically allocated string.
	free(buffer);
	return str;
}

// Function to prompt for a single character input (Y/y for yes and any other character for no) from stdin.
// This function reads a single character from stdin and clears the input buffer up to the next newline character or end of file (EOF).
// Returns:
//   - true if the user entered 'Y' or 'y'.
//   - false for any other character, including EOF.
bool prompt_for_input() {
    // Read a single character from stdin.
    char chr = (char)fgetc(stdin);

    // Clear the input buffer up to the next newline character or EOF.
    clear_input_stream(stdin);

    // Check if the character is 'Y' or 'y', indicating a positive response (yes).
    // If true, return true; otherwise, return false for a negative response (no).
    return (chr == 'y' || chr == 'Y') ? true : false;
}

// Function to split a given string into words based on whitespace characters (space, tab, newline).
// Parameters:
//   - str: The input string to be split into words.
//   - words: A pointer to a char** variable that will hold the array of words.
//            Note: The function allocates memory for the words array, which should be freed by the caller.
//   - num_words: A pointer to an int variable that will hold the number of words found in the input string.
// Returns:
//   - True if at least one word was found, false otherwise.

bool split_string_into_words(const char* str, char*** words, size_t* num_words) {
    size_t word_count = 0;

    // Allocate memory to store the words array.
    *words = (char**)malloc(sizeof(char*));

    // Create a mutable copy of the input string.
    char* mutable_str = create_string(strlen(str));
    strlcpy(mutable_str, str, sizeof(mutable_str));

    // Tokenize the mutable string based on whitespace characters.
    char* token = strtok(mutable_str, " \n\t");

    // Loop through each token and store them in the words array.
    while (token != NULL) {
        // Create a temporary string to hold the token.
        char* temp_token = create_string(strlen(token));
        strlcpy(temp_token, token, sizeof(temp_token));

        // Allocate memory for the word and store it in the words array.
        (*words)[word_count] = create_string(strlen(temp_token));
        strlcpy((*words)[word_count], temp_token, strlen(temp_token));
        word_count++;

        // Reallocate memory for the words array to accommodate the next word.
        *words = (char**)realloc(*words, (word_count + 1) * sizeof(char*));

        // Continue tokenizing the string to find the next word.
        token = strtok(NULL, " \n\t");

        // Free the temporary token string.
        free(temp_token);
    }

    // Free the temporary mutable string.
    free(mutable_str);

    // Update the number of words found.
    *num_words = word_count;

    // Return true if at least one word was found, otherwise return false.
    return (word_count > 0);
}

// Function to parse a string and convert it into a dynamic array of doubles.
// Parameters:
//   - str: The input string to be parsed.
//   - arr: A pointer to a double* variable that will hold the dynamically allocated array of doubles.
//          Note: The function allocates memory for the array, which should be freed by the caller.
//   - size: A pointer to a size_t variable that will hold the number of elements in the array.
// Returns:
//   - True if the parsing and conversion were successful, false otherwise.

bool parse_string(const char* str, double** arr, size_t* size) {
    char** words = NULL;

    size_t num_words = 0;
    bool has_words = split_string_into_words(str, &words, &num_words);

    if (!has_words) {
	free(words);
        return false;
    }
    // Allocate memory for the array of doubles and convert each word to a double.
    *arr = create_double_arr(num_words);
    for (size_t i = 0; i < num_words; i++) {
        (*arr)[i] = word_to_double(words[i]);
    }

    // Update the number of elements in the array and free the memory used by the words array.
    *size = num_words;
    destroy_mat((void**)words, (size_t)num_words);

    return true;
}

// Function to convert a string to a double number.
// Parameters:
//   - str: The input string to be converted.
// Returns:
//   - The double value represented by the input string.
double word_to_double(const char* str) {
    double num = 0.0;
    char* endptr;

    // Calculate the length of the input string.
    size_t length = strlen(str);

    // Create a sanitized copy of the input string.
    char* sanitized_str = filter_string(str);
    if (sanitized_str == NULL) {
        return num;
    }

    // Calculate the length of the sanitized string.
    length = strlen(sanitized_str);

    // Create a temporary string to store the exponent part if present.
    char* temp_str = create_string(length);
    memcpy(temp_str, sanitized_str, length);

    // If the sanitized string contains 'e', handle the exponent part separately.
    if (contain_chars(sanitized_str, 'e')) {
        // Extract the exponent part from the sanitized string.
        cut_string_left(&sanitized_str, 'e');
        cut_string_right(&temp_str, 'e');
        remove_char(sanitized_str, 'e');

        // Convert the exponent part to a double and calculate the exponent.
        double exponent = pow(10, strtod(sanitized_str, &endptr));

        // Convert the remaining part of the string to a double and multiply by the exponent.
        num = strtod(temp_str, &endptr);
        num = num * exponent;
    } else {
        // If no exponent part is present, convert the entire sanitized string to a double.
        num = strtod(sanitized_str, &endptr);
    }

    // Free the memory used for temporary strings.
    destroy_arr((void*)temp_str);
    destroy_arr((void*)sanitized_str);

    return num;
}

// Function to remove all occurrences of a character from a given string in place.
// Parameters:
//   - str: The input string from which the character will be removed.
//   - chr: The character to be removed from the string.
void remove_char(char* str, char chr) {
    char* src = str;
    char* dst = str;

    // Iterate through the string while copying characters, excluding the specified character 'chr'.
    while (*src) {
        *dst = *src++;
        dst += (*dst != chr);
    }
    *dst = '\0';
}

// Function to increase the size of a string and copy its content to the new memory location.
// Parameters:
//   - str: The original string whose size will be increased.
//   - size: The additional size to be added to the original string.
// Returns:
//   - A new string with increased size, containing the content of the original string.
char* increase_string_size(char* str, size_t size) {
    size_t currsize = strlen(str);
    // Create a new string with increased size and copy the content of the original string.
    char* new_str = create_string(currsize + size);
    memcpy(new_str, str, currsize + 1);
    free(str); // Free the memory used by the original string.
    return new_str;
}
// Function to cut the string on the right side of the last occurrence of a character 'chr'.
// Parameters:
//   - str: The input string that will be modified.
//   - chr: The character at which the string will be cut.
void cut_string_right(char** str, char chr) {
    // Find the last occurrence of the character 'chr' in the string.
    char* char_pos = strrchr(*str, chr);
    if (char_pos != NULL) {
        // Calculate the index of the character found in the string.
        size_t end_index = (size_t)char_pos - (size_t)*str;

        // Null-terminate the string at the found character position to cut it on the right side.
        (*str)[end_index] = '\0';

        // Create a new string by duplicating the modified part of the original string.
        char* new_str = strdup(*str);
        if (new_str != NULL) {
            free(*str); // Free the original string's memory.
            *str = new_str; // Update the pointer to the new string.
        } else {
            // If memory allocation fails, return or handle the error accordingly.
            return;
        }
    }
}

// Function to cut the string on the left side of the first occurrence of a character 'chr'.
// Parameters:
//   - str: The input string that will be modified.
//   - chr: The character at which the string will be cut.
void cut_string_left(char** str, char chr) {
    // Find the first occurrence of the character 'chr' in the string.
    char* char_pos = strchr(*str, chr);
    if (char_pos != NULL) {
        // Calculate the index of the character found in the string.
        size_t start_index = (size_t)char_pos - (size_t)*str;

        // Create a new string by duplicating the modified part of the original string.
        char* new_str = strdup(&(*str)[start_index]);
        if (new_str != NULL) {
            free(*str); // Free the original string's memory.
            *str = new_str; // Update the pointer to the new string.
        } else {
            // If memory allocation fails, return or handle the error accordingly.
            return;
        }
    }
}

// Function to check if a string contains a specific character 'chr'.
// Parameters:
//   - str: The input string to be checked.
//   - chr: The character to be searched in the string.
// Returns:
//   - 'true' if the character is found in the string, 'false' otherwise.
bool contain_chars(const char* str, char chr) {
    // Check if the character 'chr' is present in the string using strchr function.
    // If it is present, the function returns a non-NULL value (pointer to the first occurrence of the character),
    // indicating that the character is found in the string.
    return strchr(str, chr) != NULL;
}
// Function to compress the input string by removing all space characters ' ' in-place.
// Parameters:
//   - str: The input string that will be compressed.
void compress_string(char* str) {
    char* dest = str;
    
    // Iterate over each character in the string.
    while (*str) {
        // If the current character is not a space ' ', copy it to the destination.
        if (*str != ' ') {
            *dest = *str;
            dest++;
        }
        str++;
    }
    
    // Null-terminate the destination to complete the compressed string.
    *dest = '\0';
}

// Function to remove all occurrences of a character 'chr' in the string, except for the first one.
// Parameters:
//   - str: The input string that will be modified.
//   - chr: The character to be preserved in the string.
void remove_all_chars_except_first(char* str, char chr) {
    size_t length = strlen(str);
    bool first_found = false;

    // Iterate over each character in the string.
    for (size_t i = 0; i < length; i++) {
        // If the character 'chr' is found.
        if (str[i] == chr) {
            // If the first occurrence of the character has been found.
            if (first_found) {
                // Remove the character from the string starting from the current position.
                remove_char(str + i, chr); 
            } else {
                // Mark that the first occurrence of the character is found.
                first_found = true; 
            }
        }
    }
}

// Function to convert all characters in the string to lowercase.
// Parameters:
//   - str: The input string that will be converted to lowercase.
void convert_to_lowercase(char* str) {
    // Iterate over each character in the string.
    while (*str != '\0') {
        // Convert the current character to lowercase using the tolower function.
        *str = (char)tolower(*str);
        str++;
    }
}
// Function to filter the input string, keeping only characters in the set "allowed_chars" and removing other characters.
// Parameters:
//   - unfiltered_str: The input string to be filtered.
// Returns:
//   - A new dynamically allocated string containing the filtered characters.
//     If the filtered string is empty, returns NULL.
char* filter_string(const char* unfiltered_str) {
    // Create a copy of the input string to work with.
    size_t length = strlen(unfiltered_str);
    char* str = create_string(length);
    memcpy(str, unfiltered_str, length);

    // Convert the string to lowercase.
    convert_to_lowercase(str);

    // Define the allowed characters that will be kept in the filtered string.
    char allowed_chars[] = "-.0123456789e";

    // Iterate over each character in the string.
    for (size_t i = 0; i < length; i++) {
        // If the current character is not in the set of allowed characters, replace it with a space ' '.
        if (!contain_chars(allowed_chars, str[i])) {
            str[i] = ' ';
        }
    }

    // Compress the string by removing spaces ' ' in-place.
    compress_string(str);

    // If the filtered string is empty, free the memory and return NULL.
    if (strlen(str) == 0) {
        free(str);
        return NULL;
    }

    // If the filtered string contains 'e', perform additional processing.
    if (contain_chars(str, 'e')) {
        // Remove all characters except the first occurrence of 'e' from the string.
        remove_all_chars_except_first(str, 'e');

        // Create a copy of the string to work with the part after 'e'.
        length = strlen(str);
        char* temp_str = create_string(length);
        memcpy(temp_str, str, length);

        // Cut the string to keep the part after 'e' in temp_str and the part before 'e' in str.
        cut_string_left(&temp_str, 'e');
        cut_string_right(&str, 'e');

        // Handle negative signs for both parts.
        if (is_negative(str)) {
            remove_all_chars_except_first(str, '-');
        } else {
            remove_char(str, '-');
        }
        if (is_negative(temp_str + 1)) {
            remove_all_chars_except_first(temp_str, '-');
        } else {
            remove_char(temp_str, '-');
        }

        // Remove decimal points from both parts.
        if (contain_chars(str, '.')) {
            remove_all_chars_except_first(str, '.');
        }
        if (contain_chars(temp_str, '.')) {
            remove_all_chars_except_first(temp_str, '.');
        }

        // Increase the size of the str string to accommodate both parts and concatenate them.
        str = increase_string_size(str, strlen(str) + strlen(temp_str));
        strcat(str, temp_str);

        // Free the temporary string.
        destroy_arr((void*)temp_str);
    } else {
        // If the string does not contain 'e', handle negative sign and decimal point.
        if (is_negative(str)) {
            remove_all_chars_except_first(str, '-');
        } else {
            remove_char(str, '-');
        }
        if (contain_chars(str, '.')) {
            remove_all_chars_except_first(str, '.');
        }
    }

    // Return the filtered and processed string.
    return str;
}
// Function to check if the given string starts with a negative sign '-'.
// Parameters:
//   - str: The input string to check.
// Returns:
//   - True if the string starts with '-', otherwise false.
bool is_negative(const char* str) {
    return str[0] == '-';
}

// Function to add a double value to the end of a dynamically allocated array of doubles.
// If the array is full (size == capacity), the capacity is increased to accommodate more elements.
// Parameters:
//   - arr: Pointer to the dynamically allocated array of doubles.
//   - size: Pointer to the current size of the array (number of elements).
//   - capacity: Pointer to the current capacity of the array (maximum number of elements it can hold).
//   - num: The double value to be added to the array.
void add_double_to_array(double **arr, size_t *size, size_t *capacity, double num) {
    if (*size == *capacity) {
        increase_capacity(arr, capacity);
    }

    (*arr)[*size] = num;
    (*size)++;
}

// Function to print the contents of a 2D integer matrix.
// Parameters:
//   - mat_in: Pointer to the 2D integer matrix.
//   - rows: The number of rows in the matrix.
//   - cols: The number of columns in the matrix.
void print_int_mat(const int **mat_in, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
		printf("[ ");
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", mat_in[i][j]);
        }
        printf(" ]\n");
    }
}

// Function to print the contents of a 2D double matrix with a specified precision.
// Parameters:
//   - mat_in: Pointer to the 2D double matrix.
//   - rows: The number of rows in the matrix.
//   - cols: The number of columns in the matrix.
//   - prec: The precision to use when printing the double values.
void print_double_mat(double **mat_in, const size_t rows, const size_t cols, const int prec) {
    for (size_t i = 0; i < rows; i++) {
		printf("[ ");
        for (size_t j = 0; j < cols; j++) {
            printf("%.*f ", prec, mat_in[i][j]);
        }
		printf("]\n");
    }
    printf("\n");
}

// Function to calculate the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
// Parameters:
//   - num1: The first integer.
//   - num2: The second integer.
// Returns:
//   - The greatest common divisor of num1 and num2.
int gcd(int num1, int num2) {
    int frstnum = num1;
    int scndnum = num2;

    // Make sure both numbers are non-negative.
    if (frstnum < 0) {
        frstnum = -frstnum;
    }
    if (scndnum < 0) {
        scndnum = -scndnum;
    }

    // Handle special cases where one number is zero or one or both numbers are equal.
    if (scndnum == 0 || scndnum == 1 || frstnum == scndnum) {
        return frstnum;
    }
    if (frstnum == 0 || frstnum == 1) {
        return scndnum;
    }

    // Apply the Euclidean algorithm to calculate the GCD.
    while (frstnum != scndnum) {
        if (frstnum > scndnum) {
            frstnum -= scndnum;
        } else {
            scndnum -= frstnum;
        }
    }

    return frstnum;
}

// Function to check if a given number is a perfect square.
// Parameters:
//   - num: The number to check.
// Returns:
//   - True if the number is a perfect square, otherwise false.
bool is_perfect_square(int n) {

    // if (n < 0) // Check if the number is negative.
    //     return 0; // Negative numbers are not perfect squares.

    // if (n == 0 || n == 1)
    //     return 1; // 0 and 1 are considered perfect squares.

    // int x = n / 2; // Initialize x to half of the input number.

    // while (x * x > n) { // Loop until x^2 is greater than the number.
    //     x = (x + n / x) / 2; // Newton's method to find the square root approximation.
    // }

    return (get_int_square_root(n)*get_int_square_root(n) == n); // Check if the approximation is the exact square root.
}

// Function to calculate the integer square root of a given number.
// The integer square root is the largest integer whose square is less than or equal to the given number.
// If the input number is negative, the function returns -1 as the square root of a negative number is not defined.
// Parameters:
//   - n: The number for which to calculate the integer square root.
// Returns:
//   - The integer square root of the input number or -1 if the number is negative.
int get_int_square_root(int n) {
    if (n < 0) {
        return -1; // Отрицательные числа не имеют целочисленного квадратного корня.
    }

    if (n == 0 || n == 1) {
        return n; // Возвращаем 0 или 1, так как они являются своими квадратными корнями.
    }

    int sqnum = n / 2; // Инициализируем x половиной исходного числа.

    while (sqnum * sqnum > n) { // Пока x^2 больше исходного числа.
        sqnum = (sqnum + n / sqnum) / 2; // Метод сокращенного возведения в степень для приближенного квадратного корня.
    }

    // Проверяем разницу между квадратом x и исходным числом.
    // Если разница меньше или равна 1, возвращаем x, иначе возвращаем x + 1.
    return (sqnum * sqnum >= n) ? sqnum : sqnum+1;
}

