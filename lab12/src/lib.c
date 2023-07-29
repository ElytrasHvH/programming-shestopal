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
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++) {
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
    for (int i = 0; i < size; i++) {
        matrix[i] = (double *)malloc(sizeof(double) * size);
        for (int j = 0; j < size; j++) {
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
    int* arr = (int *)malloc(sizeof(int) * (unsigned)size);
    for (int i = 0; i < size; i++) {
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
    double* arr = (double *)malloc(sizeof(double) * (unsigned)size);
    for (int i = 0; i < size; i++) {
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
    for (int i = 0; i < size; i++) {
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

// Function to calculate the determinant of a double precision matrix
double get_determinant(double **mat, int size) {
    double det = 1;
    // Create a clone of the input matrix to perform Gaussian elimination without modifying the original matrix
    double **mat_clone = create_double_mat(size, false, 0, 0);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            mat_clone[row][col] = mat[row][col];
        }
    }

    for (int index = 0; index < size; index++) {
        int max_index = index;
        // Find the row with the maximum absolute value in the current column to use as a pivot
        for (int j = index + 1; j < size; j++) {
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
        for (int j = index + 1; j < size; j++) {
            mat_clone[index][j] /= mat_clone[index][index];
        }

        // Perform elimination on the rest of the rows to create zeros in the current column
        for (int j = 0; j < size; j++) {
            if (j != index && fabs(mat_clone[j][index]) > 1e-9) {
                for (int k = index + 1; k < size; k++) {
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

// Function to calculate the adjugate matrix of a double precision matrix and store it in adj
void get_adj_matrix(double **mat, double **adj, int size) {
    // If the matrix size is 1, the adjugate matrix consists of a single element equal to 1
    if (size == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    // Create a temporary matrix to store cofactors
    double **temp = create_double_mat(size, false, 0, 0);

    // Iterate over all elements of the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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
void swap_rows(void **mat, int row1, int row2) {
    void *temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}

// Function to convert a one-dimensional array to a 2D matrix
double **convert_array_to_mat(const double *arr, size_t count, int *size) {
    // Calculate the size of the matrix based on the number of elements in the array
    *size = (int)round(sqrt((double)count));

    // If the number of elements in the array is a perfect square, create a square matrix
    // of size sqrt(count) x sqrt(count) and populate it with elements from the array.
    if (*size * *size == count) {
        double **mat = create_double_mat(*size, 0, 0, 0);
        for (int i = 0; i < *size; i++) {
            for (int j = 0; j < *size; j++) {
                if (i * *size + j < (signed int)count) {
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
    *size = (int)ceil(sqrt((double)count));
    double **mat = create_double_mat(*size, 0, 0, 0);
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if (i * *size + j < (signed int)count) {
                mat[i][j] = arr[i * *size + j];
            } else {
                mat[i][j] = 0.0;
            }
        }
    }
    return mat;
}

void skip_whitespace(char **str) {
    while (**str != '\0' && (isspace(**str) || **str == '\n')) {
        (*str)++;
    }
}

double *read_input(FILE *stream, size_t *counter) {
    size_t capacity = 10;
    size_t size = 0;
    double *arr = create_double_arr((int)capacity);

    if (arr == NULL) {
        (void)fprintf(stderr, "Ошибка выделения памяти для массива.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    char *ptr;

    // Read the first line of input
    if (fgets(buffer, sizeof(buffer), stream) == NULL) {
        // Empty input
        *counter = 0;
        free(arr); // Free the allocated memory
        return NULL;
    }

    // Process the first line to extract numbers
    ptr = buffer;
    while (*ptr != '\0' && *ptr != '\n') {
        if (*ptr == '\0' || *ptr == '\n') {
            break; // End of line
        }

        skip_whitespace(&ptr);

        // Parse the number
        double num;
        if (parse_double(ptr, &num)) {
            if (size == capacity) {
                increase_capacity(&arr, &capacity);
            }

            arr[size] = num;
            size++;

            // Move ptr to the end of the parsed number
            while (*ptr != '\0' && !isspace(*ptr) && *ptr != '\n') {
                ptr++;
            }
        } else {
            // If the conversion fails, move the pointer to the next character
            ptr++;
        }
    }

    *counter = size;
    return arr;
}

// Helper function to read and parse the input file
void read_and_parse_input(FILE *stream, double **arr, size_t *size, size_t *capacity) {
    char buffer[1024];
    char *ptr;
    double num;

    while (fgets(buffer, sizeof(buffer), stream) != NULL) {
        ptr = buffer;
        while (*ptr != '\0' && *ptr != '\n') {
            skip_whitespace(&ptr);

            if (*ptr == '\0' || *ptr == '\n') {
                break; // End of line
            }

            if (parse_double(ptr, &num)) {
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
    }
}

// Helper function to read and parse one line of input
bool read_and_parse_line(const char *input_line, double **arr, size_t *size, size_t *capacity) {
    char buffer[1024];
    strncpy(buffer, input_line, sizeof(buffer));

    char *ptr = buffer;
    double num;

    while (*ptr != '\0' && *ptr != '\n') {
        skip_whitespace(&ptr);

        if (*ptr == '\0' || *ptr == '\n') {
            break; // End of line
        }

        if (parse_double(ptr, &num)) {
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

    return true;
}

bool parse_double(const char *str, double *result) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (isspace(*str)) {
        str++;
    }

    bool negative = false;
    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    double num = 0.0;
    bool has_numeric_part = parse_integer_part(&str, &num);

    bool has_decimal_part = parse_decimal_part(&str, &num);

    if (!has_numeric_part || has_decimal_part) {
        return false;
    }

    parse_exponent(&str, &num);

    while (isspace(*str)) {
        str++;
    }

    if (*str != '\0') {
        return false;
    }

    *result = negative ? -num : num;
    return true;
}

bool parse_integer_part(const char **str, double *num) {
    bool has_numeric_part = false;
    while (isdigit(**str)) {
        *num = *num * 10.0 + (**str - '0');
        has_numeric_part = true;
        (*str)++;
    }
    return has_numeric_part;
}

bool parse_decimal_part(const char **str, double *num) {
    int decimal_count = 0;
    double decimal = 0.1;

    while (**str == '.' && decimal_count == 0) {
        (*str)++;
        decimal_count = 1;
    }

    while (isdigit(**str)) {
        *num += (**str - '0') * decimal;
        decimal *= 0.1;
        (*str)++;
    }

    return decimal_count == 1;
}

bool parse_exponent(const char **str, double *num) {
    if (**str == 'e' || **str == 'E') {
        (*str)++;

        bool exp_negative = false;
        if (**str == '-') {
            exp_negative = true;
            (*str)++;
        } else if (**str == '+') {
            (*str)++;
        }

        int exp_val = 0;
        while (isdigit(**str)) {
            exp_val = exp_val * 10 + (**str - '0');
            (*str)++;
        }

        double exp_factor = 1.0;
        while (exp_val > 0) {
            exp_factor *= 10.0;
            exp_val--;
        }

        if (exp_negative) {
            *num /= exp_factor;
        } else {
            *num *= exp_factor;
        }
        return true;
    }
    return false;
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
void print_int_mat(int **mat_in, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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
void print_double_mat(double **mat_in, int rows, int cols, int prec) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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
