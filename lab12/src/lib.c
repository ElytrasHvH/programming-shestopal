
#include "lib.h"
#include <ctype.h>
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

// Function to create an integer matrix of given size
int **create_int_mat(size_t size, bool randomize, int limit, int shift) {
    // Ensure the minimum size of 1 for the matrix
    if (size < 1) {
        size = 1;
    }
    // Allocate memory for the matrix
    int **matrix = (int **)malloc(sizeof(int *) * size);
    for (size_t i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * size);
        for (size_t j = 0; j < size; j++) {
            // Randomize matrix elements if 'randomize' is true, otherwise initialize with zeros
            if (randomize) {
                matrix[i][j] = generate_random_int_value(limit, shift);
            } else {
                matrix[i][j] = 0; // Initialization of a matrix with zeros
            }
        }
    }
    return matrix;
}

// Function to create a double precision matrix of given size
double **create_double_mat(size_t size, bool randomize, double limit, double shift) {
    // Ensure the minimum size of 1 for the matrix
    if (size < 1) {
        size = 1;
    }
    // Allocate memory for the matrix
    double **matrix = (double **)malloc(sizeof(double *) * size);
    for (size_t i = 0; i < size; i++) {
        matrix[i] = (double *)malloc(sizeof(double) * size);
        for (size_t j = 0; j < size; j++) {
            // Randomize matrix elements if 'randomize' is true, otherwise initialize with zeros
            if (randomize) {
                matrix[i][j] = generate_random_double_value(limit, shift);
            } else {
                matrix[i][j] = 0; // Initialization of a matrix with zeros
            }
        }
    }
    return matrix;
}

// Function to create an integer array of given size, initialized with zeros
int *create_int_arr(size_t size) {
    if (size < 1) {
        return NULL;
    }
    // Allocate memory for the array and initialize its elements to zero
    int* arr = (int *)malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
    return arr;
}

// Function to create a double precision array of given size, initialized with zeros
double *create_double_arr(size_t size) {
    if (size < 1) {
        return NULL;
    }
    // Allocate memory for the array and initialize its elements to zero
    double* arr = (double *)malloc(sizeof(double) * size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
    return arr;
}

// Function to deallocate memory allocated for an array
void destroy_arr(void* arr) {
    free(arr);
}

// Function to deallocate memory allocated for a matrix
void destroy_mat(void **matrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Helper function to increase the capacity (2x)
void increase_capacity(double **arr, size_t *capacity) {
    *capacity *= 2;
    double *temp = (double *)realloc(*arr, *capacity * sizeof(double));
    if (temp == NULL) {
        (void)fprintf(stderr, "Ошибка перераспределения памяти для массива.\n");
        free(*arr);
        exit(EXIT_FAILURE);
    }
    *arr = temp;
}

// Function to generate a random integer value within the given limit and shift
int generate_random_int_value(int limit, int shift) {
    // Initialize variables to store the random value and the resulting value
    int rand_val;
    int random_value;
    
    // Check the limit to determine how to generate the random value
    if (limit > 0) {
        // If limit is positive, generate a random value in the range [0, limit - 1] and apply the shift
        rand_val = (int)random() % limit;
        // Handle potential overflow or underflow after applying the shift
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        // If limit is negative, generate a random value in the range [-limit, -1] and apply the shift
        rand_val = -((int)random() % -limit);
        // Handle potential overflow or underflow after applying the shift
        if (shift > 0 && rand_val > INT_MAX - shift) {
            random_value = INT_MAX; // Prevent integer overflow
        } else if (shift < 0 && rand_val < INT_MIN - shift) {
            random_value = INT_MIN; // Prevent integer underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        // If limit is 0, generate a random value in the full integer range and apply the shift
        rand_val = (int)random();
        // Handle potential overflow or underflow after applying the shift
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

// Function to generate a random double value within the given limit and shift
double generate_random_double_value(double limit, double shift) {
    // Initialize variables to store the random value and the resulting value
    double rand_val;
    double random_value;
    
    // Check the limit to determine how to generate the random value
    if (limit > 0) {
        // If limit is positive, generate a random value in the range [0, limit) and apply the shift
        rand_val = (double)random() / RAND_MAX * limit;
        // Handle potential overflow or underflow after applying the shift
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Random value generation with limit and shift
        }
    } else if (limit < 0) {
        // If limit is negative, generate a random value in the range [-limit, 0) and apply the shift
        rand_val = -((double)random() / RAND_MAX * -limit);
        // Handle potential overflow or underflow after applying the shift
        if (shift > 0 && rand_val > DBL_MAX - shift) {
            random_value = DBL_MAX; // Prevent double overflow
        } else if (shift < 0 && rand_val < DBL_MIN - shift) {
            random_value = DBL_MIN; // Prevent double underflow
        } else {
            random_value = rand_val + shift; // Invert limit and make values negative
        }
    } else {
        // If limit is 0, generate a random value in the range [0, 1) and apply the shift
        rand_val = (double)random() / RAND_MAX;
        // Handle potential overflow or underflow after applying the shift
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

// Function to perform bubble sort on an integer array
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


// Function to calculate the square of an integer matrix and store the result in mat_out
void square_mat(int **mat_in, int **mat_out, int size) {
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


// Function to extract the diagonal elements of a double precision matrix and store them in an array
double *diagonal(double **mat_in, double *arr, int size) {
    for (int i = 0; i < size; i++) {
        *(arr + i) = *(*(mat_in + i) + i);
    }
    return arr;
}

// Function to calculate the inverse of a double precision matrix mat_in and store it in mat_out
bool adj_reverse_mat(double **mat_in, double **mat_out, size_t size) {
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
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            mat_out[i][j] = adj[i][j] / det;
        }
    }

    // Free memory
    destroy_mat((void**)adj, size);
    return true;
}

// Function to calculate the determinant of a double precision matrix
double get_determinant(double **mat, size_t size) {
    double det = 1;
    // Create a clone of the input matrix to perform Gaussian elimination without modifying the original matrix
    double **mat_clone = create_double_mat(size, false, 0, 0);
    for (size_t row = 0; row < size; row++) {
        for (size_t col = 0; col < size; col++) {
            mat_clone[row][col] = mat[row][col];
        }
    }

    for (size_t index = 0; index < size; index++) {
        size_t max_index = index;
        // Find the row with the maximum absolute value in the current column to use as a pivot
        for (size_t j = index + 1; j < size; j++) {
            if (fabs(mat_clone[j][index]) > fabs(mat_clone[max_index][index])) {
                max_index = j;
            }
        }

        // If the pivot element is too close to zero, the determinant is 0 (matrix is singular)
        if (fabs(mat_clone[max_index][index]) < 1e-9) {
            // Free memory and return 0 to indicate failure
            destroy_mat((void**)mat_clone, size);
            return 0;
        }

        // Swap the current row with the row of the maximum element (partial pivoting)
        swap_rows((void**)mat_clone, index, max_index);

        // Update the determinant with the value of the pivot element
        det *= mat_clone[index][index];

        // Normalize the current row
        for (size_t j = index + 1; j < size; j++) {
            mat_clone[index][j] /= mat_clone[index][index];
        }

        // Perform elimination on the rest of the rows to create zeros in the current column
        for (size_t j = 0; j < size; j++) {
            if (j != index && fabs(mat_clone[j][index]) > 1e-9) {
                for (size_t k = index + 1; k < size; k++) {
                    mat_clone[j][k] -= mat_clone[index][k] * mat_clone[j][index];
                }
            }
        }
    }

    // Free memory and return the determinant
    destroy_mat((void**)mat_clone, size);
    return det;
}

// Function to get the cofactor matrix by excluding the specified row and column from the input matrix
void get_cofactor(double **mat, double **temp, size_t p_index, size_t q_index, size_t size) {
    size_t i_index = 0;
    size_t j_index = 0;
    // Iterate over all elements of the matrix
    for (size_t row = 0; row < size; row++) {
        for (size_t col = 0; col < size; col++) {
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

// Function to calculate the adjugate matrix of a double precision matrix and store it in adj
void get_adj_matrix(double **mat, double **adj, size_t size) {
    // If the matrix size is 1, the adjugate matrix consists of a single element equal to 1
    if (size == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    // Create a temporary matrix to store cofactors
    double **temp = create_double_mat(size, false, 0, 0);

    // Iterate over all elements of the matrix
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            // Calculate the cofactor for the current element
            get_cofactor(mat, temp, i, j, size);
            // Calculate the sign for the current element (used for determinant calculation)
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            // Calculate the determinant of the cofactor and store it in the adjugate matrix
            adj[j][i] = sign * get_determinant(temp, size - 1);
        }
    }

    // Free memory
    destroy_mat((void**)temp, size);
}

// Function to swap two rows of a matrix
void swap_rows(void **mat, size_t row1, size_t row2) {
    void *temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}

// Function to convert a one-dimensional array to a 2D matrix
double **convert_array_to_mat(const double *arr, size_t count, size_t *size) {
    // Calculate the size of the matrix based on the number of elements in the array
    *size = (size_t)round(sqrt((double)count));

    // If the number of elements in the array is a perfect square, create a square matrix
    // of size sqrt(count) x sqrt(count) and populate it with elements from the array.
    if (*size * *size == count) {
        double **mat = create_double_mat(*size, 0, 0, 0);
        for (size_t i = 0; i < *size; i++) {
            for (size_t j = 0; j < *size; j++) {
                if (i * *size + j < count) {
                    mat[i][j] = arr[i * *size + j];
                } else {
                    mat[i][j] = 0.0;
                }
            }
        }
        return mat;
    }

    // If the number of elements is not a perfect square, create a square matrix of size
    // ceil(sqrt(count)) x ceil(sqrt(count)) and fill it with elements from the array.
    // Any remaining elements in the matrix that do not have corresponding elements in the array
    // are filled with zeros.
    *size = (size_t)ceil(sqrt((double)count));
    double **mat = create_double_mat(*size, 0, 0, 0);
    for (size_t i = 0; i < *size; i++) {
        for (size_t j = 0; j < *size; j++) {
            if (i * *size + j < count) {
                mat[i][j] = arr[i * *size + j];
            } else {
                mat[i][j] = 0.0;
            }
        }
    }
    return mat;
}

// Helper function to skip white spaces
const char* skip_whitespace(const char* str) {
    while (isspace(*str)) {
        str++;
    }
    return str;
}

// Helper function to parse the sign (+/-) of the number
bool parse_sign(const char** str, bool* negative) {
    if (**str == '-') {
        *negative = true;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }
    return true;
}

// Helper function to parse the numeric part of the double
bool parse_numeric_part(const char** str, double* num, int* decimal_count) {
    bool has_numeric_part = false;
    while (isdigit(**str) || **str == '.') {
        if (**str == '.') {
            (*decimal_count)++;
        } else {
            has_numeric_part = true;
            *num = *num * 10 + (**str - '0');
            if (*decimal_count > 0) {
                (*decimal_count)++;
            }
        }
        (*str)++;
    }
    return has_numeric_part;
}

// Helper function to parse the exponent part of the double
bool parse_exponent(const char** str, int* exp_val, bool* exp_negative) {
    if (**str == 'e' || **str == 'E') {
        (*str)++;
        if (**str == '-') {
            *exp_negative = true;
            (*str)++;
        } else if (**str == '+') {
            (*str)++;
        }
        while (isdigit(**str)) {
            *exp_val = *exp_val * 10 + (**str - '0');
            (*str)++;
        }
        return true;
    }
    return false;
}

// Main function to parse the double
bool custom_parse_double(const char* str, double* result) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    str = skip_whitespace(str);

    bool negative = false;
    parse_sign(&str, &negative);

    double num = 0;
    int decimal_count = 0;
    bool has_numeric_part = parse_numeric_part(&str, &num, &decimal_count);

    bool has_exponent = false;
    int exp_val = 0;
    bool exp_negative = false;
    parse_exponent(&str, &exp_val, &exp_negative);

    str = skip_whitespace(str);

    if (*str != '\0' && *str != '\n') {
        return false;
    }

    if (has_numeric_part || decimal_count > 0 || has_exponent) {
        *result = negative ? -num : num;
        return true;
    }

    return false;
}



double* read_input(FILE *stream,size_t *counter) {
    char input_line[256]; // Assuming a maximum line length of 255 characters
    double* arr = NULL;
    size_t size = 0;
    size_t capacity = 0;

    // Read the input line
    if (fgets(input_line, sizeof(input_line), stream) == NULL) {
        // Error or end of file
        if (*counter == 0) {
            (*counter)++;
            printf("No input entered. Exiting(count).\n");
            return NULL;
        }
    }

    // Flush stdin to handle buffering issues
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    // Check if input_line contains any non-whitespace characters
    bool has_input = false;
    for (size_t i = 0; input_line[i] != '\0'; i++) {
        if (!isspace(input_line[i])) {
            has_input = true;
            break;
        }
    }

    if (!has_input) {
        // No input given
        printf("No input given. Exiting(arr).\n");
        return NULL;
    }

    // Trim the newline character if present
    size_t input_line_length = strlen(input_line);
    if (input_line[input_line_length - 1] == '\n')
        input_line[input_line_length - 1] = '\0';

    // Call the parsing function
    bool parse_result = read_and_parse_line(input_line, &arr, &size, &capacity);

    if (parse_result) {
        // Parsing successful, return the parsed array
        *counter = 0; // Reset the counter
        return arr;
    } else {
        // Parsing failed, free the allocated memory and return NULL
        free(arr);
        return NULL;
    }
}


bool read_and_parse_line(const char *input_line, double **arr, size_t *size, size_t *capacity) {
    size_t input_length = strlen(input_line);

    // Allocate memory for buffer dynamically
    char *buffer = (char *)malloc(sizeof(char)*(input_length + 1)); // +1 for null terminator

    if (buffer == NULL) {
        // Memory allocation failed
        (void)fprintf(stderr, "Memory allocation error.\n");
        return false;
    }

    // Copy input_line to buffer and manually add null terminator
    strcpy(buffer, input_line);

    const char *ptr = buffer;
    double num;

    while (*ptr != '\0' && *ptr != '\n') {
        ptr = skip_whitespace(ptr);

        if (*ptr == '\0' || *ptr == '\n') {
            break; // End of line
        }

        if (custom_parse_double(ptr, &num)) {
            add_double_to_array(arr, size, capacity, num);

            // Move ptr to the end of the parsed number
            while (*ptr != '\0' && !isspace(*ptr) && *ptr != '\n') {
                ptr++;
            }
        } else {
            // If the conversion fails, move the pointer to the next character
            ptr++;
        }
    }

    // Don't forget to free the dynamically allocated memory
    free(buffer);

    return true;
}

// Helper function to add a double to the array
void add_double_to_array(double **arr, size_t *size, size_t *capacity, double num) {
    if (*size == *capacity) {
        increase_capacity(arr, capacity);
    }

    (*arr)[*size] = num;
    (*size)++;
}

// Function to print an integer matrix to the console
void print_int_mat(int **mat_in, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (j == 0) {
                printf("[\t");
            }
            printf("%d\t", mat_in[i][j]);
            if (j == cols - 1) {
                printf("]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Function to print a double precision matrix to the console
void print_double_mat(double **mat_in, size_t rows, size_t cols, int prec) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (j == 0) {
                printf("[\t");
            }
            printf("%.*f\t", prec, mat_in[i][j]);
            if (j == cols - 1) {
                printf("]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Function to find the greatest common divisor (GCD) of two integers
int gcd(int num1, int num2) {
    int frstnum = num1;
    int scndnum = num2;

    // Handling negative numbers by taking absolute values
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
