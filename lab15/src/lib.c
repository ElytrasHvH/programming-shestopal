#include "lib.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <libgen.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#ifdef _WIN32
#define random() rand()
#define srandom(seed) srand(seed)
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755)
#endif

#define BUFFER_SIZE 2

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
	if(size<1) {
		return NULL;
	}
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
if(arr!=NULL)   {
	    free(arr);
        arr=NULL;
    }
}


// Function to free the memory allocated for a dynamic 2D array (matrix) of void pointers.
// Parameters:
//   - matrix: A pointer to the 2D array (matrix) of void pointers to be freed.
//   - size: The size of the square matrix (number of rows) to be freed.
void destroy_mat(void **matrix, size_t size) {
    // Check if the matrix pointer is not NULL.
    if (matrix != NULL) {
        // Iterate over the rows of the matrix.
        for (size_t i = 0; i < size; i++) {
            // Check if the row pointer is not NULL.
            if (matrix[i] != NULL) {
                // Free the memory associated with each row (1D array) of the matrix.
                free(matrix[i]);
                matrix[i]=NULL;
            }
        }
        // Free the memory associated with the array of row pointers (matrix).
        free(matrix);
        matrix=NULL;
    }
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
	
	// Generate random value depending on presence/sign of the limit
	if (limit == 0) {
    		rand_val = (int)random();
	} else if (limit > 1) {
    		rand_val = (int)random() % limit;
	} else {
    		rand_val = -((int)random() % -limit);
	}

	// Check for int overflow and react accordingly
	if (shift > 0 && rand_val > INT_MAX - shift) {
	        rand_val = INT_MAX;
	} else if (shift < 0 && rand_val < INT_MIN - shift) {
	        rand_val = INT_MIN;
	} else {
	        rand_val += shift;
	}
		
	// Return the final random value.
	return rand_val;
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
    // Generate a random double precision floating-point value in the range [0, limit] or [limit,0] (if limit is negative)
    // The random() function generates random integer values in the range [0, RAND_MAX].
    // To get a random value in the range [0, 1], divide by RAND_MAX.
    // Then we multiply random value by the factor of limit (if it's not 0)	
    rand_val = (double)random() / RAND_MAX;
    if((fabs(limit - 0) > DBL_MIN)) {
    	rand_val*=limit;
    }
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

// Function to perform matrix inversion using LU decomposition with partial pivoting.
// Parameters:
//   - mat_in: A pointer to the input square matrix (2D double array).
//   - mat_out: A pointer to the output matrix that stores the inverted matrix (2D double array).
//   - size: The size of the square matrix (number of rows and columns).
// Returns:
//   - A boolean value indicating whether the matrix inversion was successful (true) or if the matrix is singular (false).
bool inverse_mat(double **mat_in, double **mat_out, size_t size) {
    // Define a threshold for considering the determinant as zero (singular matrix).
    const double det_threshold = 1e-7;

    // Calculate the determinant of the input matrix.
    double determinant = get_determinant(mat_in, size);

    // If the determinant is close to zero, the matrix is singular and cannot be inverted.
    // Return false to indicate the failure of matrix inversion.
    if (fabs(determinant) < det_threshold) {
        return false;
    }

    // Create a new 2D double matrix and an integer array to hold the pivot information for LU decomposition.
    double **lu_matrix = create_double_mat(size, false, 0, 0);
    int *pivot = create_int_arr(size);

    // Perform LU decomposition with pivoting on the input matrix.
    lu_decomposition(mat_in, size, lu_matrix, pivot);

    // Create temporary arrays to hold intermediate values during solving of the equation AX = I for X.
    double *b_vec = create_double_arr(size);
    double *x_vec = create_double_arr(size);

    // Solve the equation AX = I for X using forward and backward substitution.
    for (int j = 0; j < (int)size; j++) {
        // Set up the vector b with the j-th unit column vector.
        for (int i = 0; i < (int)size; i++) {
            b_vec[i] = (pivot[i] == j) ? 1.0 : 0.0;
        }

        // Perform forward and backward substitution to find the j-th column of the inverted matrix.
        lu_solve(lu_matrix, size,(const double *)b_vec, x_vec);

        // Copy the result (j-th column of the inverted matrix) to the output matrix.
        for (size_t i = 0; i < size; i++) {
            mat_out[i][j] = x_vec[i];
        }
    }

    // Clean up allocated memory and return true indicating successful matrix inversion.
    destroy_mat((void **)lu_matrix, size);
    free(pivot);
    free(b_vec);
    free(x_vec);
    return true;
}


// Function to perform LU decomposition with partial pivoting
// This function takes the input matrix `mat`, its `size` (number of rows/columns),
// and performs LU decomposition with partial pivoting. LU decomposition
// represents the matrix as the product of a lower triangular matrix (L)
// and an upper triangular matrix (U). It also keeps track of row swaps using `pivot` array.
void lu_decomposition(double** mat, size_t size, double** lu_matrix, int* pivot) {
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
            swap_rows((void**)lu_matrix, i, max_index); // Casting to void** for the generic swap_rows function.

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
	if (size == 1) {
	        return mat[0][0];
    } 	
	if (size == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
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
    lu_decomposition(mat_clone, size, lu_matrix, pivot);

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

// Function to solve a linear system of equations using LU decomposition.
// Parameters:
//   - lu_mat: A pointer to the LU decomposition of the coefficient matrix (2D double array).
//   - size: The size of the matrix and vectors (number of rows and columns).
//   - vec_b: A pointer to the right-hand side vector of the system (1D double array).
//   - vec_x: A pointer to the solution vector of the system (1D double array).
// The function directly modifies the 'vec_x' vector to store the solution.
void lu_solve(double **lu_mat, size_t size,const double *vec_b, double *vec_x) {
    // Forward substitution: Solve L * y = vec_b for y.
    for (size_t i = 0; i < size; i++) {
        vec_x[i] = vec_b[i];
        for (size_t j = 0; j < i; j++) {
            vec_x[i] -= lu_mat[i][j] * vec_x[j];
        }
    }

    // Backward substitution: Solve U * x = y for x.
    for (int i = (int)size - 1; i >= 0; i--) {
        for (int j = i + 1; j < (int)size; j++) {
            vec_x[i] -= lu_mat[i][j] * vec_x[j];
        }
        vec_x[i] /= lu_mat[i][i];
    }
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

// Function to convert a 1D array into a square matrix.
// Parameters:
//   - arr: A pointer to the input 1D array of double values.
//   - count: The number of elements in the input array.
//   - size: A pointer to a size_t variable that will store the size of the square matrix (number of rows and columns).
// Returns:
//   - A pointer to the dynamically allocated 2D matrix (square matrix) containing the values from the input array.
//     The caller is responsible for freeing the allocated memory.
double **convert_array_to_mat(const double *arr, size_t count, size_t *size) {
    // Calculate the square root of the count and cast it to size_t to get the matrix size.
    (*size) = (size_t)get_int_square_root((int)count);

    // Create a new square matrix with the calculated size.
    // The create_double_mat function initializes the matrix elements to zero.
    double **mat_out = create_double_mat(*size, 0, 0, 0);

    // Fill the matrix with values from the input array in row-major order.
    for (size_t i = 0; i < *size; i++) {
        for (size_t j = 0; j < *size; j++) {
            // Calculate the index in the 1D array corresponding to the (i, j) element in the matrix.
            // The elements are arranged in row-major order in the 1D array.
            size_t index = (*size) * i + j;
            // Assign the value from the input array to the matrix element.
            // The matrix is square, so the number of columns is the same as the matrix size.
            mat_out[i][j] = arr[index];
        }
    }

    // Return the dynamically allocated square matrix.
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
void clear_input_line(FILE *stream) {
    int clear;
    // Loop through the input stream until a newline character or EOF is encountered.
    // This effectively clears the input buffer up to the next line or end of file.
    while ((clear = fgetc(stream)) != '\n' && clear != EOF) {
        // Do nothing; the loop discards the characters read from the input stream.
    }
}


// Function to read a line of input from the standard input (stdin).
// The function dynamically allocates memory to store the input line as a C-style string.
// The function uses a buffer size of 8192 characters to read the input line.
// Returns:
//   - A pointer to the dynamically allocated C-style string containing the input line.
//     The caller is responsible for freeing the allocated memory.
//   - If the input line is empty or an error occurs, the function returns NULL.
char* read_input_line() {
    // Define the buffer size for reading the input line.
    const size_t buffer_size = 8192;

    // Variable to store the length of the input line.
    size_t temp_length = 0;

    // Create a new C-style string (character array) with the specified buffer size.
    char* str = create_string(buffer_size);

    // Read the input line from the standard input (stdin) using the specified buffer size.
    // The function fscanf reads up to 8191 non-newline characters (limited by the buffer size)
    // and stores them in the 'str' buffer until a newline or the end of the file is encountered.
    if (fscanf(stdin, "%8191[^\n]", str) == 1) {
        // If characters were successfully read, clear the remaining input stream until the newline character.
        clear_input_line(stdin);

        // Calculate the length of the input line (excluding the null terminator and newline character, if present).
        while (str[temp_length] != '\0' && str[temp_length] != '\n') {
            temp_length++;
        }

        // If the input line is empty (length is zero), free the memory and return NULL.
        if (temp_length == 0) {
            free(str);
            return NULL;
        }

        // Return the dynamically allocated C-style string containing the input line.
        return str;

    } 
    // If an error occurs during input or no characters were read, clear the input stream and free the memory.
    clear_input_line(stdin);
    free(str);
    return NULL;
}

// Function to read 8192 characters long input from the standard input (stdin).
// The function dynamically allocates memory to store the input as a C-style string.
// The function uses a buffer size of 8192 characters to read the input.
// Returns:
//   - A pointer to the dynamically allocated C-style string containing the input.
//     The caller is responsible for freeing the allocated memory.
//   - If the input is empty or an error occurs, the function returns NULL.
char* read_input() {
    // Define the buffer size for reading the input.
    const size_t buffer_size = 8192;

    // Variable to store the length of the input.
    size_t length = 0;

    // Create a new C-style string (character array) with the specified buffer size.
    char* str = create_string(buffer_size);

    // Check if memory allocation was successful.
    if (str == NULL) {
        // If memory allocation failed, return NULL to indicate an error.
        return NULL;
    }

    // Read the input from the standard input (stdin) using the specified buffer size.
    // The function fscanf reads up to 8192 characters (limited by the buffer size)
    // and stores them in the 'str' buffer until the end of the file is encountered.
    if (fscanf(stdin, "%8192c", str) <= 0) {
        // If an error occurs during input or no characters were read, free the memory.
        free(str);
        return NULL;
    }

    // Count the length of the input.
    while (str[length] != '\0') {
        length++;
    }

    // If the input is empty (length is zero), free the memory and return NULL.
    if (length == 0) {
        free(str);
        return NULL;
    }

    // Return the dynamically allocated C-style string containing the input.
    return str;
}

// Function to read whole input from the standard input (stdin).
// The function dynamically allocates memory to store the input as a C-style string.
// The function uses a looped call of a function reading 8192 characters per read to read input
// Returns:
//   - A pointer to the dynamically allocated C-style string containing the input.
//     The caller is responsible for freeing the allocated memory.
//   - If the input is empty or an error occurs, the function returns NULL.
char* read_all_input() {
    // Define the buffer size for reading the input.
    const size_t buffer_size = 8192;

    // Variable to store the length of the input.
    size_t length = 0;

    // Create a new C-style string (character array) with the specified buffer size. string size is (buffer_size + '\0')
    char* str = create_string(buffer_size);

    // Check if memory allocation was successful.
    if (str == NULL) {
        // If memory allocation failed, return NULL to indicate an error.
        return NULL;
    }

    // Read the input from the standard input (stdin) using the specified buffer size.
    char* chunk;
    while ((chunk = read_input()) != NULL) {
        // Calculate the length of the chunk (excluding the null terminator).
        size_t chunk_length = strlen(chunk);

        // Reallocate memory for the string to accommodate more characters.
        str = realloc(str, length + chunk_length + 1);

        // Append the chunk to the end of the string.
        memcpy(str + length, chunk, chunk_length);
        length += chunk_length;

        // Free the memory used by the chunk.
        free(chunk);
    }

    // Add a null terminator at the end of the string just to be sure
    str[length] = '\0';

    // Return the dynamically allocated C-style string containing the input.
    return str;
}

// Function to prompt for a single character input (Y/y for yes and any other character for no) from stdin.
// This function reads a single character from stdin and clears the input buffer up to the next newline character or end of file (EOF).
// Returns:
//   - true if the user entered 'Y' or 'y'.
//   - false for any other character, including EOF.
bool prompt_for_input() {
    char buffer[BUFFER_SIZE];

    // Read up to 1 character from stdin into the buffer.
    if (fscanf(stdin, "%1[^\n]", buffer) == 1) {
        clear_input_line(stdin);

        // Check if the first character in the buffer is 'Y' or 'y', indicating a positive response (yes).
        // If true, return true; otherwise, return false for a negative response (no).
        return (buffer[0] == 'y' || buffer[0] == 'Y') ? true : false;
    } 
        clear_input_line(stdin);
        return false;
    
}


// Function to split a given string into words based on whitespace characters (space, tab, newline).
// Parameters:
//   - str: The input string to be split into words.
//   - words: A pointer to a char** variable that will hold the array of words.
//            Note: The function allocates memory for the words array, which should be freed by the caller.
//   - num_words: A pointer to an int variable that will hold the number of words found in the input string.
// Returns:
//   - True if at least one word was found, false otherwise.

bool split_string_into_words(const char* str, char*** words, size_t* num_words, const char* delimiter) {
    size_t word_count = 0;

    if(words==NULL) {
        return false;
    }
    // Tokenize the input string to count the number of words.
    char* mutable_str = strdup(str);
    char* token = strtok(mutable_str, delimiter);

    while (token != NULL) {
        word_count++;
        token = strtok(NULL, delimiter);
    }
    if(word_count==0){
	free(mutable_str);
	*num_words = 0;
	return false; //no words were in the string
    }    
    // Allocate memory for the words array based on the actual count of words.
    *words = (char**)malloc(word_count * sizeof(char*));

    if (*words == NULL) {
        free(mutable_str);
        return false;  // Memory allocation failed.
    }

    // Tokenize the input string again to populate the words array.
    strcpy(mutable_str, str);
    token = strtok(mutable_str, delimiter);

    for (size_t i = 0; i < word_count; i++) {
        (*words)[i] = strdup(token);
        token = strtok(NULL, delimiter);
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
if(arr==NULL||size==NULL||str==NULL) {
    return false;
}
char** words = NULL;

size_t num_words = 0;
bool has_words = split_string_into_words(str, &words, &num_words, " \n\t");
if (!has_words) {
if(words!=NULL){
	free(words);
}
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
    double base = 10;
    // Create a sanitized copy of the input string.
    char* sanitized_str = filter_number_string(str);
    if (sanitized_str == NULL) {
        return num;
    }
    // Calculate the length of the sanitized string.
    size_t length = strlen(sanitized_str);

    // Create a temporary string to store the exponent part if present.
    char* temp_str = create_string(length);
    memcpy(temp_str, sanitized_str, length);

    // If the sanitized string contains 'e', handle the exponent part separately.
    if (contains_char(sanitized_str, 'e')) {
        // Extract the exponent part from the sanitized string.
        cut_string_left(&sanitized_str, 'e');
        cut_string_right(&temp_str, 'e');
        remove_char(sanitized_str, 'e');

        // Convert the exponent part to a double and calculate the exponent.
        double exponent = pow(base, strtod(sanitized_str, &endptr));

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
        size_t end_index = (size_t)(char_pos - *str);

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
        size_t start_index = (size_t)(char_pos - *str);

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
bool contains_char(const char* str, char chr) {
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
        // If the current character is not a whitespace/tab/newline, copy it to the destination.
        if ((*str != ' ')&&(*str != '\t')&&(*str != '\n')) {
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

// Function to filter the input string, keeping only characters that are in the set of allowed characters and removing other characters.
// Parameters:
//   - unfiltered_str: The input string to be filtered.
//   - allowed_chars: A C-style string containing the set of allowed characters.
// Returns:
//   - A new dynamically allocated string containing the filtered characters.
//     If the filtered string is empty, returns NULL.
char* filter_string(const char* unfiltered_str, const char* allowed_chars) {
    
    if (allowed_chars==NULL||unfiltered_str==NULL) {
        return NULL;
    }
    // Create a hash set to store the characters in allowed_chars.
    bool allowed[256] = {false};
    for (size_t i = 0; i < strlen(allowed_chars); i++) {
        allowed[(unsigned char)allowed_chars[i]] = true;
    }
    // Create a copy of the input string to work with.
    size_t length = strlen(unfiltered_str);
    char* str = NULL;
    str = create_string(length);
    if(str==NULL) {
        return NULL;
    }
    memcpy(str, unfiltered_str, length + 1);

    // Iterate over each character in the string.
    for (size_t i = 0; i < length; i++) {
        // If the current character is not in the set of allowed characters, replace it with a space ' '.
        if (!allowed[(unsigned char)str[i]]) {
            str[i] = ' ';
        }
    }

    // Return the filtered string.
    return str;
}

// Function to filter the input string, keeping only characters that are used to represent numbers and removing other characters.
// Parameters:
//   - unfiltered_str: The input string to be filtered.
// Returns:
//   - A new dynamically allocated string containing the filtered characters.
//     If the filtered string is empty, returns NULL.
char* filter_number_string(const char* unfiltered_str) {
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
        if (!contains_char(allowed_chars, str[i])) {
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
    if (contains_char(str, 'e')) {
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
        if (contains_char(str, '.')) {
            remove_all_chars_except_first(str, '.');
        }
        if (contains_char(temp_str, '.')) {
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
        if (contains_char(str, '.')) {
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
		printf("[\t");
        for (size_t j = 0; j < cols; j++) {
            printf("%d\t", mat_in[i][j]);
        }
        printf("]\n");
    }
}

// Function to print the contents of a 2D double matrix with a specified precision.
// Parameters:
//   - mat_in: Pointer to the 2D double matrix.
//   - rows: The number of rows in the matrix.
//   - cols: The number of columns in the matrix.
//   - prec: The precision to use when printing the double values.
void print_double_mat(double **mat_in, const size_t rows, const size_t cols, const int prec) {
    // Determine the maximum number of characters required to represent any element in each column
    int *max_width = calloc(cols, sizeof(int));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            int width = snprintf(NULL, 0, "%.*f", prec, mat_in[i][j]);
            if (width > max_width[j]) {
                max_width[j] = width;
            }
        }
    }

    // Print the matrix using the determined field width for each column
    for (size_t i = 0; i < rows; i++) {
        printf("[\t");
        for (size_t j = 0; j < cols; j++) {
            printf("%*.*f\t", max_width[j], prec, mat_in[i][j]);
        }
        printf("]\n");
    }
    printf("\n");

    free(max_width);
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
        return -1; // Negative numbers don't have sqrt (we don't talk about complex numbers here)
    }

    if (n == 0 || n == 1) {
        return n; // Returning 0 and 1 as is
    }

    int sqnum = n >> 1; // initializing as half of the initial number

    while (sqnum * sqnum > n) { // while half^2 is > than n
        sqnum = (sqnum + n / sqnum) >> 1; // adjusting the number to get closer to the square root
    }
    return (sqnum * sqnum >= n) ? sqnum : sqnum + 1; // checking if the adjusted number squared is equal to or greater than n
}

// Function to check the validity of input and output file paths.
// Parameters:
//   - input_file: The path of the input file.
//   - output_file: The path of the output file.
// Returns:
//   - 0 if input and/or output file paths are valid, -1 otherwise.
int check_files(char* input_file, char* output_file) {
    if (output_file == NULL && input_file == NULL) {
        // Both input_file and output_file are NULL, return error
        return -1;
    }
    
    if (input_file != NULL) {
        size_t input_file_len = strlen(input_file);
        if (input_file_len > 0 && (input_file[input_file_len - 1] == '/' || isspace(input_file[input_file_len - 1]))) {
            // Input file path ends with '/' or a whitespace character, handle error
            return -1;
        }
        
        // Check if input file is readable
        if (access(input_file, R_OK) == -1) {
            return -1;
        }
    }
    
    if (output_file != NULL) {
        // Check if output file path is valid
        size_t output_file_len = strlen(output_file);
        if (output_file_len > 0 && (output_file[output_file_len - 1] == '/' || isspace(output_file[output_file_len - 1]))) {
            // Output file path ends with '/' or a whitespace character, handle error
            return -1;
        }
        // Duplicate output_file to avoid modifying the original string
        char *output_file_dup = strdup(output_file);
        char *output_dir_path = dirname(output_file_dup);
        if (directory_exists(output_dir_path) == 0) {
            MKDIR(output_dir_path);
            
            if (directory_exists(output_dir_path) == 0) {
                // Unable to create the output directory, return error
                free(output_file_dup);
                return -1;
            }
        } else if(directory_exists(output_dir_path) == -1) {
            //dir_path is a null pointer (somehow)
            free(output_file_dup);
            return -1;
        } else {
            // Directory exists, check if it's writable
            if (access(output_dir_path, W_OK) == -1) {
                // Cannot write to the directory, handle error
                free(output_file_dup);
                return -1;
            }
        
        // Free the duplicated output_file path
        free(output_file_dup);
        }
    }
    
    return 0; // Both input and output file paths are valid
}

// Function to read content from a file and store it in a string.
// Parameters:
//   - input_file: The path of the input file to read from.
//   - result_string: Pointer to a char pointer where the result content will be stored.
//     Note: This function allocates memory for result_string using read_all_input function. Caller is responsible for freeing it
void read_from_file(char* input_file, char** result_string) {
    if (result_string == NULL||input_file==NULL) {
        return; // Return if result_string pointer is NULL.
    }
    
    //Better to use in combination with check_files function
    FILE *file = freopen(input_file, "r", stdin); // Open the input file for reading.
    if (file == NULL) {
        return; // Return if file opening fails.
    }
    
    *result_string = read_all_input(); // Read all input from stdin and store in result_string.
    (void)fclose(file); // Close the input file.
}

// Function to check if a directory exists at the given path.
// Parameters:
//   - path: The path of the directory to check.
// Returns:
//   - 1 if the directory exists, -1 if path is a NULL,0 otherwise
int directory_exists(const char *path) {
    if (path==NULL) {
        return -1;
    }
    struct stat stat_buffer;
    return (stat(path, &stat_buffer) == 0 && S_ISDIR(stat_buffer.st_mode)) ? 1 : 0;
}

// Function to write data to a file.
// Parameters:
//   - output_file: The path of the output file to write to.
//   - data: The data to be written to the file.
void write_to_file(char* output_file, char* data) {
    if (data==NULL) {
        return;
    }
    FILE *file = fopen(output_file, "w"); // Open the output file for writing.
    
    if (file == NULL) {
        // Handle error if file opening fails (e.g., permission issues).
        // Note: This function assumes that proper checks have been performed before calling it.
        return;
    }
    
    (void)fprintf(file, "%s", data); // Write the data to the file.
    (void)fclose(file); // Close the output file.
}


// Function to convert a double matrix to a formatted string.
// Parameters:
//   - mat_in: The input double matrix.
//   - rows: The number of rows in the matrix.
//   - cols: The number of columns in the matrix.
//   - prec: The precision (number of decimal places) to format the elements with.
// Returns:
//   - A dynamically allocated string containing the formatted matrix representation.
//     Note: The caller is responsible for freeing the memory allocated for the string.
char* write_double_mat_to_string(double **mat_in, const size_t rows, const size_t cols, const int prec) {
    // Determine the maximum number of characters required to represent any element in each column
    int *max_width = calloc(cols, sizeof(int));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            int width = snprintf(NULL, 0, "%.*f", prec, mat_in[i][j]);
            if (width > max_width[j]) {
                max_width[j] = width;
            }
        }
    }

    // Determine the total number of characters required for the formatted matrix
    int total_width = 0;
    for (size_t i = 0; i < rows; i++) {
        total_width += snprintf(NULL, 0, "[\t");
        for (size_t j = 0; j < cols; j++) {
            total_width += snprintf(NULL, 0, "%*.*f\t", max_width[j], prec, mat_in[i][j]);
        }
        total_width += snprintf(NULL, 0, "]\n");
    }
    total_width += snprintf(NULL, 0, "\n");

    // Allocate memory for the formatted matrix string
    char *mat_str = create_string((size_t)total_width); 
    if (mat_str == NULL) {
        free(max_width);
        return NULL;
    }

    // Write the matrix using the determined field width for each column
    char *ptr = mat_str;
    for (size_t i = 0; i < rows; i++) {
        ptr += sprintf(ptr, "[\t");
        for (size_t j = 0; j < cols; j++) {
            ptr += sprintf(ptr, "%*.*f\t", max_width[j], prec, mat_in[i][j]);
        }
        ptr += sprintf(ptr, "]\n");
    }
    ptr += sprintf(ptr, "\n");

    free(max_width);
    return mat_str;
}

// Function to parse input file and output file location. Mainly designed for use with command line arguments, but can be used elsewhere
// Parameters: 
// - argc: the number of arguments (originally designed for command line arguments)
// - argv: an array of strings containing the arguments
// - input_file: a pointer to a string to hold the extracted input file path (not formatted or verified)
// - output_file: a pointer to a string to hold the extracted output file path (not formatted or verified)
// - errstr: a pointer to a string to store error messages
// - errcode: a pointer to an integer to store error codes for caller's reference
// * input_file must be initialized as NULL pointer , errstr and output_file can be dynamically allocated strings (e.g., strdup("string") or NULL pointers
// * we only extract strings, we do NOT perform any assertions on them to check if it is a real path/file etc.
// * errcode is set to -1 if an error occurs
// ! The caller is responsible for freeing memory.
void handle_args(int argc, char** argv, char** input_file, char** output_file, char** errstr, int* errcode) {
    switch (argc) {
        case 1:
            printf("No input file provided\nGive a file location (1 line, up to 8192 characters):\n");
            *input_file = read_input_line(); // Read input file from user
            if (*input_file == NULL) {
                destroy_arr((void*)*errstr); // Free any previous error message
                *errstr = strdup("No input file provided or an error occurred.\n");
                *errcode = -1;
                break;
            }
            printf("No output file destination & name provided\nDo you want to proceed with the default location? (Y/N)\n");
            if (!prompt_for_input()) {
                destroy_arr(*output_file); // Free any previous output file path
                printf("Give output file destination (1 line, up to 8192 characters):\n");
                *output_file = read_input_line(); // Read output file path from user
                if (*output_file == NULL) {
                    destroy_arr((void*)*errstr);
                    *errstr = strdup("No destination provided or an error occurred.\n");
                    *errcode = -1;
                    break;
                }
            }
            break;
        case 2:
            *input_file = strdup(argv[1]); // Extract input file path from command line argument
            printf("No output file destination & name provided\nDo you want to proceed with the default location? (Y/N)\n");
            if (!prompt_for_input()) {
                destroy_arr(*output_file);
                printf("Give output file destination (1 line, up to 8192 characters):\n");
                *output_file = read_input_line();
                if (*output_file == NULL) {
                    destroy_arr((void*)*errstr);
                    *errstr = strdup("No destination provided or an error occurred.\n");
                    *errcode = -1;
                    break;
                }
            }
            break;
        default:
            destroy_arr(*output_file);
            *input_file = strdup(argv[1]); // Extract input file path from command line argument
            *output_file = strdup(argv[2]); // Extract output file path from command line argument
            break;
    }

    if ((*input_file == NULL) && (*output_file == NULL)) {
        destroy_arr((void*)*errstr);
        *errstr = strdup("No input and output file were provided.\n");
        *errcode = -1;
        return;
    }
}

// Function to handle output based on error codes
// Parameters:
// - output_text: the text to be outputted or written to the file
// - output_file: the file path to write the output text (assumed to have write permission)
// - errstr: the error message text
// - errcode: the error code
// * Error codes 1 and -1 reserved for problems with the output file (nonexistent, not given, etc.)
// * Error codes other than 1 and -1 are considered general errors.
// * Assumes that write permission to the output file is already granted.
void handle_output(char* output_text, char* output_file, char* errstr, int errcode) {
    // errcode 1, -1 reserved for problems with the output file (nonexistent, not given, no write permission, etc.)
    switch (errcode) {
        case 0:
            printf("%s", output_text); // Print output text to console
            write_to_file(output_file, output_text); // Write output text to the specified file
        break;

        case -1:
        case 1:
            printf("%s", errstr); // Print error message to console
        break;

        default:
            printf("%s", errstr); // Print error message to console
            write_to_file(output_file, errstr); // Write error message to the specified file
        break;

    }
}

// The bitmap_t must have the same number of elements as the collection of workcollectionmember_s.
// For example, if there are SIZE members in the collection, then the size of the bitmap_t should also be SIZE.
bool search_field(const workcollectionmember_s* member ,bitmap_t map ,const size_t size ,const field_t field ,const searchdata_u* data) {
    size_t match = 0;
    switch (field) {

        case FREQUENCY:
        for(size_t i = 0; i < size; i++){
            map[i] |= (member[i].base.frequency == data->frequency_value);
            match += map[i];
        }
        break;

        case LABWORKTYPE:
        for(size_t i=0; i<size;i++){
            map[i] |= (member[i].lab_work.type == data->labwork_type_value);
            match += map[i];
        }
        break;
        
        case PROF_SURNAME:
        for(size_t i=0; i<size;i++){
            map[i]|=(strcmp(data->string,member[i].base.subject.prof_surname)==0);
            match+=map[i];
        }
        break;
    
        case SUBJECT_NAME:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(strcmp(data->string,member[i].base.subject.subject_name)==0);
            match+=(size_t)map[i];
        }
        break;
    
        case HAS_VARIATION:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(data->bool_value==member[i].base.has_variation);
            match+=(size_t)map[i];
        }
        break;
    
        case THEME:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(strcmp(data->string,member[i].base.subject.subject_name)==0);
            match+=(size_t)map[i];
        }
        break;
        
        case PROBLEM_COUNT:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(data->unsigned_int_value==member[i].base.problem_count);
            match+=(size_t)map[i];
        }
        break;
        
        case HAS_TEST_QUESTIONS:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(data->bool_value==member[i].work_type.has_test_questions);
            match+=(size_t)map[i];
        }
        break;
        
        case HAS_PRACTICAL_TASKS: 
        for(size_t i=0; i<size;i++) {
            map[i]|=(bool)(data->bool_value==member[i].work_type.has_practical_tasks);
            match+=(size_t)map[i];
            }
        break;
        
        case IS_POSSIBLE_AT_HOME:
        for(size_t i=0; i<size;i++){
            map[i]|=(bool)(data->bool_value==member[i].lab_work.is_possible_at_home);
            match+=(size_t)map[i];
        }
        break;
        default:
        break;
    }
    return match>0;
}

// This function parses input data and populates a collection of workcollectionmember_s structures.
// It expects a comma or(and) newline-separated input string, and it fills in the struct_ptr array with parsed data.
// If there are any errors during parsing, it sets an error code and error message.
/* 
 * * * * * * * * * * * Order of data * * * * * * * * * * *
 * Frequency: An enum value between 0 and 4 (1-3).       *
 * LabWorkType: An enum value between 0 and 5 (1-4).     *
 * Professor’s Surname: A string of up to 255 characters.*
 * Subject Name: A string of up to 255 characters.       *
 * Has Variation: A boolean value (0 or 1).              *
 * Theme: A string of up to 1023 characters.             *
 * Problem Count: An unsigned integer value.             *
 * Has Practical Tasks: A boolean value (0 or 1).        *
 * Has Test Questions: A boolean value (0 or 1).         *
 * Is Possible At Home: A boolean value (0 or 1).        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
void parse_data(const char* input_str, char** errstr, int* errcode, workcollectionmember_s* struct_ptr, size_t size) {
    char** words = NULL;    // Array to store words extracted from the input string
    size_t num_words = 0;   // Number of words in the input string
    size_t struct_count = 0; // Number of structs to be filled in the struct_ptr array
    // Split the input string into words using commas and newlines as separators
    if (!split_string_into_words(input_str, &words, &num_words, ",\n")) {
        // If splitting fails, set an error and return
        set_error(errcode, errstr, 2, "Data parsing failed\n");
        return;
    }
    // Calculate the number of structs to be filled based on the number of words
    struct_count = (num_words / 10 > size) ? size : num_words / 10;
    // Check if the number of words is not evenly divisible by 10
    if (num_words % 10 != 0) {
        // If not, set an error and free allocated memory before returning
        set_error(errcode, errstr, 3, "Data is not aligned properly\n");
        destroy_mat((void**)words, num_words);
        return;
    }
    // Loop through the input words and fill in the struct_ptr array        
    for(size_t struct_num = 0;struct_num<struct_count;struct_num++) {
        // Parse and assign values to the struct members based on word indices
        struct_ptr[struct_num].base.frequency=((word_to_double(words[struct_num*10])) > 0 && (size_t)(word_to_double(words[struct_num*10]))<4 ) ? (frequency_t)word_to_double(words[struct_num*10]): 0;
        struct_ptr[struct_num].lab_work.type=((word_to_double(words[struct_num*10+1])) > 0 && (size_t)(word_to_double(words[struct_num*10+1]))<5 ) ? (labwork_t)word_to_double(words[struct_num*10+1]): 0;
        strncpy(struct_ptr[struct_num].base.subject.prof_surname,words[struct_num*10+2],255);
        struct_ptr[struct_num].base.subject.prof_surname[255]='\0';
        strncpy(struct_ptr[struct_num].base.subject.subject_name,words[struct_num*10+3],255);
        struct_ptr[struct_num].base.subject.subject_name[255]='\0';
        struct_ptr[struct_num].base.has_variation=(!(fabs(fmod(word_to_double(words[struct_num*10+4]),1))>0) && (word_to_double(words[struct_num*10+4])) > -1 && (word_to_double(words[struct_num*10+4]))<2 ) ? (bool)word_to_double(words[struct_num*10+4]): 0;
        strncpy(struct_ptr[struct_num].base.theme,words[struct_num*10+5],1023);
        struct_ptr[struct_num].base.theme[1023]='\0';
        struct_ptr[struct_num].base.problem_count=(!(fabs(fmod(word_to_double(words[struct_num*10+6]),1))>0) && word_to_double(words[struct_num*10+6])) ? (unsigned int)word_to_double(words[struct_num*10+6]) : 0;
        struct_ptr[struct_num].work_type.has_practical_tasks=(!(fabs(fmod(word_to_double(words[struct_num*10+7]),1))>0) && (word_to_double(words[struct_num*10+7])) > -1 && (word_to_double(words[struct_num*10+7]))<2 ) ? (bool)word_to_double(words[struct_num*10+7]): 0;
        struct_ptr[struct_num].work_type.has_test_questions=(!(fabs(fmod(word_to_double(words[struct_num*10+8]),1))>0) && (word_to_double(words[struct_num*10+8])) > -1 && (word_to_double(words[struct_num*10+8]))<2 ) ? (bool)word_to_double(words[struct_num*10+8]): 0;
        struct_ptr[struct_num].lab_work.is_possible_at_home=(!(fabs(fmod(word_to_double(words[struct_num*10+9]),1))>0) && (word_to_double(words[struct_num*10+9])) > -1 && (word_to_double(words[struct_num*10+9]))<2 ) ? (bool)word_to_double(words[struct_num*10+9]): 0;
        struct_ptr[struct_num].num=struct_num;
    }
    destroy_mat((void**)words,num_words);
}

// This function sets an error code and error message. It takes pointers to an error code, an error message string,
// an error code value, and an error message to assign. It updates the error code and dynamically allocates memory for
// the error message. The previous error message is destroyed.
void set_error(int* const errcode, char** errstr, const int code, const char* errmsg) {
    *errcode = code;  // Set the error code to the provided code value

    // Destroy the previously allocated error message string
    destroy_arr((void*)*errstr);

    // Duplicate and store the new error message in errstr
    *errstr = strdup(errmsg);
}

// This function performs case insensetive string comparison
// It accepts two arguments, both of which are pointers to null-terminated strings (str1 and str2).
// The function iterates through each character in the strings simultaneously. For each pair of characters:
//     - It converts the characters to lowercase using the tolower() function.
//     - It compares the lowercase characters for equality.
// The iteration continues until it encounters a pair of characters that are not equal or until it reaches the end of one or both strings.
// If it finds a pair of characters that are not equal, it returns the difference between their ASCII values.
// If it reaches the end of both strings without finding any unequal characters (meaning the strings are equal ignoring case), it returns 0.
int stricmp(const char* str1, const char* str2) {
    // Iterate through and compare the characters
    while(*str1 && *str2 && (tolower((unsigned char)*str1) == tolower((unsigned char)*str2)))
        {
            str1++;
            str2++;
        }
    //return the difference between last 2 compared elements.
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

// This function writes information about a workcollectionmember_s in a string.
// It takes a pointer to a constant workcollectionmember_s as input.
// It formats the information into a string and returns it.
char* work_collection_member_to_string(const workcollectionmember_s* const member) {
    char* output_str = (char*)calloc(4096,sizeof(char));  // Buffer to store the formatted output string
    char problem_str[50] = {0};   // Buffer to store problem-related information

    // Arrays for converting enum values to human-readable strings
    const char* const frequency_string[NUM_FREQUENCIES] = {
        [NEVER] = "Never",
        [ONCE_A_WEEK] = "Once a week",
        [ONCE_A_MODULE] = "Once a module",
        [ONCE_A_SEMESTER] = "Once a semester"
    };
    const char* const lab_work_type_string[NUM_LAB_WORK_TYPES] = {
        [NO_TYPE] = "No type",
        [WRITE_A_PROGRAM] = "Write a program",
        [CALCULATE] = "Calculate",
        [CREATE_A_SCHEME] = "Create a scheme",
        [DO_EXPERIMENT] = "Do experiment"
    };
    // Determine the problem-related information based on has_variation flag
    if (!member->base.has_variation) {
        snprintf(problem_str, sizeof(problem_str), "It has %u problems\n", member->base.problem_count);
    } else {
        snprintf(problem_str, sizeof(problem_str), "It is variadic and has %u problems in each variant\n", member->base.problem_count);
    }
    // Format the information into the output string
    snprintf(output_str, 4096,
        "This is Lab №%u\n"
        "The subject of a work is \"%s\" "
        "Professor's surname is %s\n"
        "Theme is: \"%s\" "
        "It is done %s\n"
        "Type of the Lab is %s\n"
        "%s"  // Include the problem-related information
        "%s"  // Indicate whether it has practical tasks
        "%s"  // Indicate whether it has test questions
        "%s", // Indicate whether it's possible to do it at home
        member->num+1,
        member->base.subject.subject_name,
        member->base.subject.prof_surname,
        member->base.theme,
        frequency_string[member->base.frequency],
        lab_work_type_string[member->lab_work.type],
        problem_str,
        !member->work_type.has_practical_tasks ? 
            "It doesn't have practical tasks\n" : 
            "It has practical tasks\n",
        !member->work_type.has_test_questions ? 
            "It doesn't have test questions\n" : 
            "It has test questions\n",
        !member->lab_work.is_possible_at_home ? 
            "It's not possible to do it at home\n" : 
            "It's possible to do it at home\n"
    );
    return output_str;
}

// A helper function to compare two workcollectionmember_s by a given field.
// It takes two pointers to constant workcollectionmember_s and a field_t enum value as input.
// The function switches on the field_t and performs a comparison based on the specified field.
// Returns an integer value:
// - Negative if p_struct1's field is less than p_struct2's field.
// - Zero if p_struct1's field is equal to p_struct2's field.
// - Positive if p_struct1's field is greater than p_struct2's field.
int compare_by_field(const workcollectionmember_s* const p_struct1, const workcollectionmember_s* const p_struct2, field_t type) {
    int stricmp_val;
    switch (type)
    {
    case FREQUENCY:
        // Compare by frequency value
        return (int)p_struct1->base.frequency - (int)p_struct2->base.frequency;
    case LABWORKTYPE:
        // Compare by lab work type value
        return (int)p_struct1->lab_work.type - (int)p_struct2->lab_work.type;
    case PROF_SURNAME:
        // Compare by professor surname string
        stricmp_val = stricmp(p_struct1->base.subject.prof_surname, p_struct2->base.subject.prof_surname);
        return (stricmp_val==0) ? strcmp(p_struct1->base.subject.prof_surname, p_struct2->base.subject.prof_surname) : stricmp_val;
    case SUBJECT_NAME:
        // Compare by subject name string
        stricmp_val = stricmp(p_struct1->base.subject.subject_name, p_struct2->base.subject.subject_name);
        return (stricmp_val==0) ? strcmp(p_struct1->base.subject.subject_name, p_struct2->base.subject.subject_name) : stricmp_val;
    case HAS_VARIATION:
        // Compare by has_variation boolean
        return (int)p_struct1->base.has_variation - (int)p_struct2->base.has_variation;
    case THEME:
        // Compare by theme string
        stricmp_val = stricmp(p_struct1->base.theme, p_struct2->base.theme);
        return (stricmp_val==0) ? strcmp(p_struct1->base.theme, p_struct2->base.theme) : stricmp_val;
    case PROBLEM_COUNT:
        // Compare by problem_count unsigned int
        return (int)p_struct1->base.problem_count - (int)p_struct2->base.problem_count;
    case HAS_TEST_QUESTIONS:
        // Compare by has_test_questions boolean
        return (int)p_struct1->work_type.has_test_questions - (int)p_struct2->work_type.has_test_questions;
    case HAS_PRACTICAL_TASKS:
        // Compare by has_practical_tasks boolean
        return (int)p_struct1->work_type.has_practical_tasks - (int)p_struct2->work_type.has_practical_tasks;
    case IS_POSSIBLE_AT_HOME:
        // Compare by is_possible_at_home boolean
        return (int)p_struct1->lab_work.is_possible_at_home - (int)p_struct2->lab_work.is_possible_at_home;
    default:
        // Invalid field type, return 0
        return 0;
    }
}

// A helper function to swap two elements in an array.
// It takes a pointer to an array, along with the indices of the elements to be swapped.
// The function swaps the elements at indices i and j in the array.
void swap(void* arr, size_t i, size_t j, size_t size) {
    char temp[size];
    memcpy(temp, (char*)arr + i*size, size);  // Store the element at index i in a temporary variable
    memcpy((char*)arr + i*size, (char*)arr + j*size, size);  // Replace the element at index i with the element at index j
    memcpy((char*)arr + j*size, temp, size);  // Replace the element at index j with the element stored in the temporary variable
}

// A sorting function that uses the bubble sort algorithm to sort an array of workcollectionmember_s.
// It takes a pointer to an array of workcollectionmember_s, the count of elements in the array, and a field_t enum value as input.
// The function iterates through the array using nested loops and compares adjacent elements based on the specified field type.
void sort_struct(workcollectionmember_s* const member,const size_t member_count, const field_t type) {
    for (size_t i = member_count - 1; i > 0; i--) {
        for (size_t j = 0; j < i; j++) {
            int cmpval = compare_by_field(&member[j], &member[j+1], type);
            // Check if the comparison result flags that second member is "larger" then first
            if (cmpval < 0) {
                // Swap the elements to move the matching element to the front
                swap(member, j, j+1,sizeof(workcollectionmember_s));
            }
            // Check if the elements have the same field values and need to be sorted by 'num'
            if (cmpval == 0 && member[j].num > member[j+1].num) {
                // Swap the elements to maintain the order based on 'num'
                swap(member, j, j+1,sizeof(workcollectionmember_s));
            }
        }
    }
}