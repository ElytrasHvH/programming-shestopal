#include "../src/lib.h"
#include <check.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EPSILON 1e-7

// Test case for the create_int_arr function
START_TEST(test_create_int_arr)
{
    // Test with size 0
    int *arr = create_int_arr(0);
    ck_assert_ptr_null(arr);

    // Test with size 5
    arr = create_int_arr(5);
    ck_assert_ptr_nonnull(arr);
    for (size_t i = 0; i < 5; i++) {
        ck_assert_int_eq(arr[i], 0);
    }
    free(arr);
}
END_TEST

// Test case for the create_double_arr function
START_TEST(test_create_double_arr)
{
    // Test with size 0
    double *arr = create_double_arr(0);
    ck_assert_ptr_null(arr);

    // Test with size 5
    arr = create_double_arr(5);
    ck_assert_ptr_nonnull(arr);
    for (size_t i = 0; i < 5; i++) {
        ck_assert_double_eq_tol(arr[i], 0.0, EPSILON);
    }
    free(arr);
}
END_TEST

// Test case for the create_char_arr function
START_TEST(test_create_char_arr)
{
    // Test with size 0
    char *arr = create_char_arr(0);
    ck_assert_ptr_null(arr);

    // Test with size 5
    arr = create_char_arr(5);
    ck_assert_ptr_nonnull(arr);
    free(arr);
}
END_TEST

// Test case for the create_string function
START_TEST(test_create_string)
{
    // Test with size 0
    char *string = create_string(0);
    ck_assert_ptr_nonnull(string);
    ck_assert_str_eq(string, "");
    free(string);

    // Test with size 5
    string = create_string(5);
    ck_assert_ptr_nonnull(string);
    ck_assert_str_eq(string, "");
    free(string);
}
END_TEST

// Test case for the increase_capacity function
START_TEST(test_increase_capacity)
{
	// Create an array of size 2 and capacity 2.
	size_t capacity = 2;
	double *arr = create_double_arr(capacity);

	// Increase the capacity of the array.
	increase_capacity(&arr, &capacity);

	// Check that the capacity has been doubled.
	ck_assert_uint_eq(capacity, 4);

	free(arr);
}
END_TEST

// Test case for the generate_random_int_value function
START_TEST(test_generate_random_int_value)
{
    // Test with limit 10 and shift 0
    int value = generate_random_int_value(10, 0);
    ck_assert_int_ge(value, 0);
    ck_assert_int_lt(value, 10);

    // Test with limit -10 and shift 0
    value = generate_random_int_value(-10, 0);
    ck_assert_int_le(value, 0);
    ck_assert_int_gt(value, -10);

    // Test with limit 0 and shift 5
    value = generate_random_int_value(0, 5);
    ck_assert_int_ge(value, INT_MIN + 5);
    ck_assert_int_le(value, INT_MAX - 5);
}
END_TEST

// Test case for the generate_random_double_value function
START_TEST(test_generate_random_double_value)
{
    // Test with limit 10.0 and shift 0.0
    double value = generate_random_double_value(10.0, 0.0);
    ck_assert_double_ge(value, 0.0);
    ck_assert_double_lt(value, 10.0);

    // Test with limit -10.0 and shift 0.0
    value = generate_random_double_value(-10.0, 0.0);
    ck_assert_double_le(value, 0.0);
    ck_assert_double_gt(value, -10.0);

    // Test with limit 0.0 and shift 5.0
    value = generate_random_double_value(0.0, 5.0);
    ck_assert_double_ge(value, DBL_MIN + 5.0);
    ck_assert_double_le(value, DBL_MAX - 5.0);
}
END_TEST

// Test case for the create_int_mat function
START_TEST(test_create_int_mat)
{
    // Test with size 0, randomize false, limit 0, and shift 0
    int **mat = create_int_mat(0, false, 0, 0);
    ck_assert_ptr_nonnull(mat);
    ck_assert_ptr_nonnull(mat[0]);
    ck_assert_int_eq(mat[0][0], 0);
    destroy_mat((void**)mat,1);

    // Test with size 2, randomize true, limit 10, and shift 5
    mat = create_int_mat(2, true, 10, 5);
    ck_assert_ptr_nonnull(mat);
    for (size_t i = 0; i < 2; i++) {
        ck_assert_ptr_nonnull(mat[i]);
        for (size_t j = 0; j < 2; j++) {
            ck_assert_int_ge(mat[i][j], 5);
            ck_assert_int_lt(mat[i][j], 15);
        }
        
    }
    destroy_mat((void**)mat,2);
}
END_TEST

// Test case for the create_double_mat function
START_TEST(test_create_double_mat)
{
    // Test with size 0, randomize false, limit 0.0, and shift 0.0
    double **mat = create_double_mat(0, false, 0.0, 0.0);
    ck_assert_ptr_nonnull(mat);
    ck_assert_ptr_nonnull(mat[0]);
    ck_assert_double_eq_tol(mat[0][0], 0.0, EPSILON);
    destroy_mat((void**)mat,1);

    // Test with size 2, randomize true, limit 10.0, and shift 5.0
    mat = create_double_mat(2, true, 10.0, 5.0);
    ck_assert_ptr_nonnull(mat);
    for (size_t i = 0; i < 2; i++) {
        ck_assert_ptr_nonnull(mat[i]);
        for (size_t j = 0; j < 2; j++) {
            ck_assert_double_ge(mat[i][j], 5.0);
            ck_assert_double_lt(mat[i][j], 15.0);
        }
        
    }
    destroy_mat((void**)mat,2);
}
END_TEST

// Test case for the square_mat function
START_TEST(test_square_mat)
{
	// Create a square matrix of size 2.
	int **mat_in = create_int_mat(2, false, 0, 0);

	// Set the values of the input matrix.
	mat_in[0][0] = -1;
	mat_in[1][1] = -1;

	// Create an output matrix of size 2.
	int **mat_out = create_int_mat(2, false, 0, 0);

	// Square the input matrix and store the result in the output matrix.
	square_mat(mat_in, mat_out, 2);

	// Check that the output matrix is correct.
	ck_assert_int_eq(mat_out[1][1], 1);
    	ck_assert_int_eq(mat_out[1][1], 1);

    	destroy_mat((void**)mat_in,2);
    	destroy_mat((void**)mat_out,2);
}
END_TEST

// Test case for the bubble_sort function
START_TEST(test_bubble_sort)
{
	// Create an array of size 5.
	int *arr = create_int_arr(5);

	// Set the values of the array.
	arr[4] = -3;
	arr[3] = -4;
	arr[2] = -5;
	arr[1] = -6;
	arr[0] = -7;

	// Sort the array using bubble sort.
	bubble_sort(arr, 5);

	// Check that the array is sorted in ascending order.
	for (int i = 1; i < 5; i++) {
		ck_assert_int_le(arr[i - 1], arr[i]);
	}

	free(arr);
}
END_TEST

// Test case for the diagonal function
START_TEST(test_diagonal)
{
	// Create a square matrix of size 3.
	double **mat_in = create_double_mat(3, true, -10.5, -5.25);

	// Set the values of the input matrix.
	mat_in[2][2] = -3.25;
	mat_in[1][1] = -4.25;
	mat_in[0][0] = -5.25;

	// Create an output array of size 3.
	double *arr_out = create_double_arr(3);

	// Extract the diagonal elements of the input matrix and store them in the output array.
	diagonal(mat_in, arr_out, 3);

	// Check that the output array is correct.
	ck_assert_double_eq_tol(arr_out[2], -3.25, EPSILON);
	ck_assert_double_eq_tol(arr_out[1], -4.25, EPSILON);
	ck_assert_double_eq_tol(arr_out[0], -5.25, EPSILON);

    destroy_mat((void**)mat_in,3);
	free(arr_out);
}
END_TEST

// Test case for the lu_decomposition function
START_TEST(test_lu_decomposition)
{
    // Create a square matrix of size 3.
    double **mat = create_double_mat(3, false, 0, 0);

    // Set the values of the input matrix.
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 7;
    mat[2][1] = 8;
    mat[2][2] = 10;

    // Create an LU matrix and pivot array for LU decomposition
    double **lu_matrix = create_double_mat(3, false, 0, 0);
    int *pivot = create_int_arr(3);

    // Perform LU decomposition
    lu_decomposition(mat, 3, lu_matrix, pivot);

    // Check that the LU matrix is correct.
    ck_assert_double_eq_tol(lu_matrix[0][0], 7.0, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[0][1], 8.0, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[0][2], 10.0, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[1][0], 0.14285714285714288, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[1][1], 0.857142857142857, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[1][2], 1.571428571428572, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[2][0], 0.571428571428571, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[2][1], 0.5, EPSILON);
    ck_assert_double_eq_tol(lu_matrix[2][2], -0.5, EPSILON);

    // Check that the pivot array is correct.
    ck_assert_int_eq(pivot[0], 2);
    ck_assert_int_eq(pivot[1], 0);
    ck_assert_int_eq(pivot[2], 1);

    destroy_mat((void**)mat,3);
    destroy_mat((void**)lu_matrix,3);
	free(pivot);
}
END_TEST

// Test case for the get_determinant function
START_TEST(test_get_determinant)
{
	// Create a square matrix of size 3.
	double **mat = create_double_mat(3, false, 0, 0);

	// Set the values of the input matrix.
	mat[0][0] = -5.25;
	mat[1][1] = -4.25;
	mat[2][2] = -3.25;

	// Compute the determinant of the input matrix.
	double det = get_determinant(mat, 3);

	// Check that the determinant is correct.
	ck_assert_double_eq_tol(det, -72.515625, EPSILON);

    destroy_mat((void**)mat,3);
}
END_TEST

// Test case for the get_cofactor function
START_TEST(test_get_cofactor)
{
	// Create a square matrix of size 3.
	double **mat_in = create_double_mat(3, false, -10.5, -5.25);

	// Set the values of the input matrix.
	mat_in[0][0] = -5.25;
	mat_in[1][1] = -4.25;
	mat_in[2][2] = -3.25;

	// Create a temporary matrix of size (size - 1) to store the cofactor matrix.
	double **temp_mat = create_double_mat(2, false, 0, 0);

	// Compute the cofactor matrix for element (p_index=1,q_index=1).
	get_cofactor(mat_in,temp_mat , 1 , 1 ,3 );

	// Check that the temporary matrix is correct.
	ck_assert_double_eq_tol(temp_mat [0][0],-5.25,EPSILON );
	ck_assert_double_eq_tol(temp_mat [0][1],0,EPSILON );
	ck_assert_double_eq_tol(temp_mat [1][0],0,EPSILON );
	ck_assert_double_eq_tol(temp_mat [1][1],-3.25,EPSILON );

    destroy_mat((void**)mat_in,3);
    destroy_mat((void**)temp_mat,2);
}
END_TEST

// Test case for the get_adj_matrix function
START_TEST(test_get_adj_matrix) {
    // Define the input matrix
    double **mat = create_double_mat(3, false, 0, 0);
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
    mat[0][2] = 3.0;
    mat[1][0] = 4.0;
    mat[1][1] = 5.0;
    mat[1][2] = 6.0;
    mat[2][0] = 7.0;
    mat[2][1] = 8.0;
    mat[2][2] = 9.0;

    // Compute the adjugate matrix
    double **adj = create_double_mat(3, false, 0, 0);
    get_adj_matrix(mat, adj, 3);

    // Define the expected adjugate matrix
    double expected_adj[3][3] = {
        {-3.0, 6.0, -3.0},
        {6.0, -12.0, 6.0},
        {-3.0, 6.0, -3.0}
    };

    // Compare each element of the computed adjugate matrix with the expected values
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            ck_assert_double_eq_tol(adj[i][j], expected_adj[i][j], EPSILON);
        }
    }

    // Free memory
    destroy_mat((void**)mat, 3);
    destroy_mat((void**)adj, 3);
}
END_TEST

START_TEST(test_lu_solve) {
    const size_t size = 3; // Define the size of the matrix and vectors (number of rows and columns).
    double **lu_matrix = create_double_mat(size, false, 0, 0); // Create LU matrix (assuming you have this function).
    double **coefficient_matrix = create_double_mat(size, false, 0, 0); // Create coefficient matrix (assuming you have this function).
    double *vec_b = create_double_arr(size); // Create right-hand side vector.
    double *vec_x = create_double_arr(size); // Create solution vector.
    int *pivot = create_int_arr(size); // Create pivot array.

    // Set up the coefficient matrix and right-hand side vector for a test case.
    // For example, solve the following system of equations:
    // 2x + y + 3z = 5
    // 4x + 5y + 6z = 7
    // 7x + 8y + 9z = 10
    coefficient_matrix[0][0] = 2.0;
    coefficient_matrix[0][1] = 1.0;
    coefficient_matrix[0][2] = 3.0;
    coefficient_matrix[1][0] = 4.0;
    coefficient_matrix[1][1] = 5.0;
    coefficient_matrix[1][2] = 6.0;
    coefficient_matrix[2][0] = 7.0;
    coefficient_matrix[2][1] = 8.0;
    coefficient_matrix[2][2] = 9.0;
    vec_b[0] = 5.0; vec_b[1] = 7.0; vec_b[2] = 10.0;

    // Perform LU decomposition on the coefficient matrix.
    lu_decomposition(coefficient_matrix, size, lu_matrix, pivot);

    // Use lu_solve to find the solution vector.
    lu_solve(lu_matrix, size, vec_b, vec_x);

    // Verify the solution vector (should be [-28/3, -4/3, 9]).
    double expected_solution[] = {-9.333333333, -1.333333333, 9};
    for (size_t i = 0; i < size; i++) {
        ck_assert_double_eq_tol(vec_x[i], expected_solution[i], EPSILON);
    }

    // Clean up allocated memory.
    destroy_mat((void **)lu_matrix, size);
    destroy_mat((void **)coefficient_matrix, size);
    free(vec_b);
    free(vec_x);
    free(pivot);
}
END_TEST


// Test cases for swap_rows function.
START_TEST(test_swap_rows) {
    // Create a 2x2 matrix.
    double **mat = create_double_mat(2, false, 0, 0);
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
    mat[1][0] = 3.0;
    mat[1][1] = 4.0;

    // Swap rows 0 and 1.
    swap_rows((void **)mat, 0, 1);

    // The matrix should be swapped now with tolerance.
    ck_assert_double_eq_tol(mat[0][0], 3.0, EPSILON);
    ck_assert_double_eq_tol(mat[0][1], 4.0, EPSILON);
    ck_assert_double_eq_tol(mat[1][0], 1.0, EPSILON);
    ck_assert_double_eq_tol(mat[1][1], 2.0, EPSILON);

    // Clean up memory.
    destroy_mat((void **)mat, 2);
}
END_TEST

// Test cases for convert_array_to_mat function.
START_TEST(test_convert_array_to_mat) {
    const double arr[] = {1.0, 2.0, 3.0, 4.0};
    size_t size;

    // Convert the array to a matrix.
    double **mat = convert_array_to_mat(arr, 4, &size);

    // Check if the conversion is correct with tolerance.
    ck_assert_uint_eq(size, 2);
    ck_assert_double_eq_tol(mat[0][0], 1.0, EPSILON);
    ck_assert_double_eq_tol(mat[0][1], 2.0, EPSILON);
    ck_assert_double_eq_tol(mat[1][0], 3.0, EPSILON);
    ck_assert_double_eq_tol(mat[1][1], 4.0, EPSILON);

    // Clean up memory.
    destroy_mat((void **)mat, size);
}
END_TEST

// Test cases for skip_whitespace function.
START_TEST(test_skip_whitespace) {
    const char *str1 = "   Hello";
    const char *str2 = "Hello";
    const char *str3 = "   ";
    const char *str4 = "";

    // Test skipping leading whitespaces.
    ck_assert_str_eq(skip_whitespace(str1), "Hello");
    ck_assert_str_eq(skip_whitespace(str2), "Hello");
    ck_assert_str_eq(skip_whitespace(str3), "");
    ck_assert_str_eq(skip_whitespace(str4), "");

}
END_TEST


// Test case for the clear_input_line function
START_TEST(test_clear_input_line) {
    // Create a temporary file for stdin
    FILE *tmp = tmpfile();
    fputs("Hello\nWorld\n", tmp);
    rewind(tmp);

    // Test the function
    clear_input_line(tmp);

    // Verify that stdin is clear
    int clear = fgetc(tmp);
    ck_assert_int_eq(clear, 'W');

    // Test the function
    clear_input_line(tmp);

    // Verify that stdin is clear
    clear = fgetc(tmp);
    ck_assert_int_eq(clear,EOF);

    // Clean up
    fclose(tmp);
}
END_TEST

// Test case for the read_input_line function
START_TEST(test_read_input_line) {
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    fputs("Hello\nWorld\n", tmp);
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read a line from stdin using read_input.
    char *line = read_input_line();
    ck_assert_str_eq(line, "Hello");
    free(line);

    // Read another line from stdin using read_input and verify that it has been cleared.
    line = read_input_line();
    ck_assert_str_eq(line, "World");
    free(line);

    // Read nother line and check if NULL was returned (string is empty or nothing else left).
    line = read_input_line();
    ck_assert_ptr_null(line);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_prompt_for_input)
{
    freopen("test_prompt_for_input.txt", "w+", stdin);
    fputs("Y\n", stdin);
    rewind(stdin);
    
    ck_assert(prompt_for_input() == true);
    
    freopen("test_prompt_for_input.txt", "w+", stdin);
    fputs("y\n", stdin);
    rewind(stdin);
    
    ck_assert(prompt_for_input() == true);
    
    freopen("test_prompt_for_input.txt", "w+", stdin);
    fputs("N\n", stdin);
    rewind(stdin);
    
    ck_assert(prompt_for_input() == false);

    remove("test_prompt_for_input.txt");
}
END_TEST

START_TEST(test_split_string_into_words)
{
	char **words;
	size_t num_words;
	
	bool result = split_string_into_words("Hello world!", &words, &num_words);
	ck_assert(result == true);
	ck_assert(num_words == 2);
	ck_assert_str_eq(words[0], "Hello");
	ck_assert_str_eq(words[1], "world!");
	destroy_mat((void**)words,num_words);
	
	result = split_string_into_words("", &words, &num_words);
	ck_assert(result == false);
	
	result = split_string_into_words("   ", &words, &num_words);
	ck_assert(result == false);
}
END_TEST

// Test case for is_negative function
START_TEST(test_is_negative)
{
    ck_assert(is_negative("-123") == true);
    ck_assert(is_negative("123") == false);
    ck_assert(is_negative("") == false);
}
END_TEST

// Test case for cut_string_right function
START_TEST(test_cut_string_right)
{
    char* str1 = strdup("hello world");
    cut_string_right(&str1, ' ');
    ck_assert_str_eq(str1, "hello");
    free(str1);

    char* str2 = strdup("hello world");
    cut_string_right(&str2, 'x');
    ck_assert_str_eq(str2, "hello world");
    free(str2);

    char* str3 = strdup("");
    cut_string_right(&str3, ' ');
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

// Test case for cut_string_left function
START_TEST(test_cut_string_left)
{
    char* str1 = strdup("hello world");
    cut_string_left(&str1, ' ');
    ck_assert_str_eq(str1, " world");
    free(str1);

    char* str2 = strdup("hello world");
    cut_string_left(&str2, 'x');
    ck_assert_str_eq(str2, "hello world");
    free(str2);

    char* str3 = strdup("");
    cut_string_left(&str3, ' ');
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

// Test case for contains_char function
START_TEST(test_contains_char)
{
    ck_assert(contains_char("hello", 'h') == true);
    ck_assert(contains_char("hello", 'o') == true);
    ck_assert(contains_char("hello", 'x') == false);
}
END_TEST

// Test case for compress_string function
START_TEST(test_compress_string)
{
    char str1[] = "hello world";
    compress_string(str1);
    ck_assert_str_eq(str1, "helloworld");

    char str2[] = "   ";
    compress_string(str2);
    ck_assert_str_eq(str2, "");

    char str3[] = "";
    compress_string(str3);
    ck_assert_str_eq(str3, "");
}
END_TEST

// Test case for remove_all_chars_except_first function
START_TEST(test_remove_all_chars_except_first)
{
    char str1[] = "hello world";
    remove_all_chars_except_first(str1, 'l');
    ck_assert_str_eq(str1, "helo world");

    char str2[] = "hello world";
    remove_all_chars_except_first(str2, 'x');
    ck_assert_str_eq(str2, "hello world");

    char str3[] = "";
    remove_all_chars_except_first(str3, 'l');
    ck_assert_str_eq(str3, "");
}
END_TEST

// Test case for convert_to_lowercase function
START_TEST(test_convert_to_lowercase)
{
    char str1[] = "HELLO WORLD";
    convert_to_lowercase(str1);
    ck_assert_str_eq(str1, "hello world");

    char str2[] = "Hello World";
    convert_to_lowercase(str2);
    ck_assert_str_eq(str2, "hello world");

    char str3[] = "";
    convert_to_lowercase(str3);
    ck_assert_str_eq(str3, "");
}
END_TEST

//Test case for filter_number_string function
START_TEST(test_filter_number_string)
{
    char* result1 = filter_number_string("123.45e-6");
    ck_assert_str_eq(result1, "123.45e-6");
    free(result1);

    char* result2 = filter_number_string("abc123.45E-6def");
    ck_assert_str_eq(result2, "123.45e-6");
    free(result2);

    char* result3 = filter_number_string("abc");
    ck_assert(result3 == NULL);

    char* result4 = filter_number_string("1.2.3.4e5.6.7");
    ck_assert_str_eq(result4, "1.234e5.67");
    free(result4);

    char* result5 = filter_number_string("-1-2-3e-4-5-6");
    ck_assert_str_eq(result5, "-123e-456");
    free(result5);
}
END_TEST

// Test case for word_to_double function
START_TEST(test_word_to_double)
{
    double result1 = word_to_double("123.45e-6");
    ck_assert_double_eq_tol(result1, 123.45*pow(10,-6), EPSILON);

    double result2 = word_to_double("abc123.45E-6def");
    ck_assert_double_eq_tol(result2, 123.45*pow(10,-6), EPSILON);

    double result3 = word_to_double("abc");
    ck_assert_double_eq_tol(result3, 0, EPSILON);

    double result4 = word_to_double("1.2.3.4e5.6.7");
    ck_assert_double_eq_tol(result4, 577185.16434840256, EPSILON);

    double result5 = word_to_double("-1-2-3e-4-5-");
    ck_assert_double_eq_tol(result5,-123*pow(10,-45), EPSILON);
}
END_TEST

// Test case for parse_string function
START_TEST(test_parse_string) {
    const char *input = "3.14 2.718 1.618 -5.2e3 abc123x45yz6 7.8e-2";
    double *arr = NULL;
    size_t size = 0;

    // Call the function to be tested
    bool result = parse_string(input, &arr, &size);

    // Check if the function returns true and the size is correct
    ck_assert(result);
    ck_assert_int_eq((int)size, 6);

    // Check the values in the array
    ck_assert_double_eq_tol(arr[0], 3.14, EPSILON);
    ck_assert_double_eq_tol(arr[1], 2.718, EPSILON);
    ck_assert_double_eq_tol(arr[2], 1.618, EPSILON);
    ck_assert_double_eq_tol(arr[3], -5200.0, EPSILON);
    ck_assert_double_eq_tol(arr[4], 123456.0, EPSILON);
    ck_assert_double_eq_tol(arr[5], 0.078, EPSILON);

    // Clean up allocated memory
    free(arr);
} END_TEST

// Test case for remove_char function
START_TEST(test_remove_char) {
    char input[] = "Hello, World!";
    char expected[] = "Heo, Word!";
    char rm_char = 'l';

    remove_char(input, rm_char);

    ck_assert_str_eq(input, expected);
} END_TEST

// Test case for increase_string_size function
START_TEST(test_increase_string_size) {
    char* input = create_string(5);
    strcpy(input,"Hello");
    size_t size_increase = 5;

    char *new_str = increase_string_size(input, size_increase);

    ck_assert_str_eq(new_str, "Hello");
    ck_assert_str_eq(new_str + strlen("Hello"), ""); // Check if the remaining part is an empty string

    free(new_str);
} END_TEST

// Test case for gcd function
START_TEST(test_gcd) {
    int num1 = 48;
    int num2 = 18;
    int expected_result = 6;

    int result = gcd(num1, num2);

    ck_assert_int_eq(result, expected_result);
} END_TEST

// Test case for *is perfect square* function
START_TEST(test_is_perfect_square) {
    int perfect_square = 49;
    int non_perfect_square = 50;

    bool result1 = is_perfect_square(perfect_square);
    bool result2 = is_perfect_square(non_perfect_square);

    ck_assert(result1);
    ck_assert(!result2);
} END_TEST

// Test case for get_int_square_root function
START_TEST(test_get_int_square_root) {
    int num = 25;
    int expected_result = 5;

    int result = get_int_square_root(num);

    ck_assert_int_eq(result, expected_result);
} END_TEST

// Test case for filter_string function
START_TEST(test_filter_string)
{
    // Test case 1: Basic filtering
    char* result = filter_string("Hello, World!", "Helo, Wrd");
    ck_assert_str_eq(result, "Hello, World ");
    free(result);

    // Test case 2: Empty allowed_chars
    result = filter_string("Hello, World!", "");
    ck_assert_str_eq(result, "             ");
    free(result);

    // Test case 3: All characters allowed
    result = filter_string("Hello, World!", "Helo, Wrd!");
    ck_assert_str_eq(result, "Hello, World!");
    free(result);

    // Test case 4: Null input string
    result = filter_string(NULL, "Helo, Wrd!");
    ck_assert_ptr_eq(result, NULL);

    // Test case 5: Null allowed_chars
    result = filter_string("Hello, World!", NULL);
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_read_all_input)
{
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    fputs("This is a test.\n", tmp);
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read all input from stdin using read_all_input.
    char* result = read_all_input();
    ck_assert_str_eq(result, "This is a test.\n");
    free(result);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_read_all_input_empty)
{
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read all input from stdin using read_all_input.
    char* result = read_all_input();
    ck_assert_str_eq(result, "");
    free(result);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_read_input)
{
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    fputs("This is a test.\n", tmp);
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read input from stdin using read_input.
    char* result = read_input();
    ck_assert_str_eq(result, "This is a test.\n");
    free(result);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_read_input_empty)
{
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read input from stdin using read_input.
    char* result = read_input();
    ck_assert_ptr_null(result);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_read_all_input_long)
{
    // Redirect stdin to a temporary file.
    FILE *tmp = tmpfile();
    for (int i = 0; i < 8200; i++) {
        fputc('a', tmp);
    }
    fputc('\n', tmp);
    rewind(tmp);
    freopen("/dev/null", "r", stdin);
    dup2(fileno(tmp), STDIN_FILENO);

    // Read all input from stdin using read_all_input.
    char* result = read_all_input();
    ck_assert_uint_eq(strlen(result), 8201);
    for (int i = 0; i < 8200; i++) {
        ck_assert_int_eq(result[i], 'a');
    }
    ck_assert_int_eq(result[8200], '\n');
    free(result);

    // Close the temporary file.
    fclose(tmp);
}
END_TEST

START_TEST(test_check_files)
{
    // Test case 1: Both input_file and output_file are NULL
    ck_assert_int_eq(check_files(NULL, NULL), -1);
    
    // Test case 2: input_file is NULL, output_file is a valid path
    ck_assert_int_eq(check_files(NULL, "output.txt"), 0);
    
    // Test case 3: input_file is a valid path, output_file is NULL
    ck_assert_int_eq(check_files("assets/input.txt", NULL), 0);
    
    // Test case 4: Both input_file and output_file are valid paths
    ck_assert_int_eq(check_files("assets/input.txt", "dist/output.txt"), 0);
    
    // Test case 5: input_file is an invalid path (e.g., non-existent file)
    ck_assert_int_eq(check_files("non_existent.txt", "dist/output.txt"), -1);
    
    // Test case 6: output_file is an invalid path (e.g., non-writable directory) //! Create read-only directory to test
    ck_assert_int_eq(check_files("assets/input.txt", "dist/test/output.txt"), -1);
}
END_TEST

START_TEST(test_read_from_file)
{
    // Test case 1: input_file is NULL
    char *result_string = NULL;
    read_from_file(NULL, &result_string);
    ck_assert_ptr_eq(result_string, NULL);
    
    // Test case 2: result_string is NULL
    read_from_file("test_input.txt", NULL);
    
    // Test case 3: input_file is a valid file path
    FILE *fp = fopen("test_input.txt", "w");
    fprintf(fp, "test content\n");
    fclose(fp);
    
    read_from_file("test_input.txt", &result_string);
    ck_assert_str_eq(result_string, "test content\n");
    
    free(result_string);
}
END_TEST

START_TEST(test_directory_exists)
{
    // Test case 1: path is NULL
    ck_assert_int_eq(directory_exists(NULL), -1);
    
    // Test case 2: path is an existing directory
    ck_assert_int_eq(directory_exists("/tmp"), 1);
    
    // Test case 3: path is a non-existing directory
    ck_assert_int_eq(directory_exists("/non_existing_dir"), 0);
}
END_TEST

START_TEST(test_write_to_file)
{
    // Test case 1: output_file is NULL
    write_to_file(NULL, "test content\n");
    
    // Test case 2: data is NULL
    write_to_file("test_output.txt", NULL);
    
    // Test case 3: output_file is a valid file path
    write_to_file("test_output.txt", "test content\n");
    
    FILE *fp = fopen("test_output.txt", "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    
    ck_assert_str_eq(buffer, "test content\n");
}
END_TEST

Suite *lib_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("lib_test");

	/* Core test case */
	tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_int_arr);
    tcase_add_test(tc_core, test_create_double_arr);
    tcase_add_test(tc_core, test_create_char_arr);
    tcase_add_test(tc_core, test_create_string);
    tcase_add_test(tc_core, test_increase_capacity);
    tcase_add_test(tc_core, test_generate_random_int_value);
    tcase_add_test(tc_core, test_generate_random_double_value);
    tcase_add_test(tc_core, test_create_int_mat);
    tcase_add_test(tc_core, test_create_double_mat);
    tcase_add_test(tc_core, test_square_mat);
    tcase_add_test(tc_core, test_bubble_sort);
    tcase_add_test(tc_core, test_diagonal);
    tcase_add_test(tc_core, test_lu_decomposition);
    tcase_add_test(tc_core, test_get_determinant);
    tcase_add_test(tc_core, test_get_cofactor);
    tcase_add_test(tc_core, test_get_adj_matrix);
    tcase_add_test(tc_core, test_lu_solve);
    tcase_add_test(tc_core, test_swap_rows);
    tcase_add_test(tc_core, test_convert_array_to_mat);
    tcase_add_test(tc_core, test_skip_whitespace);
    tcase_add_test(tc_core, test_clear_input_line);
    tcase_add_test(tc_core, test_read_input_line);
    tcase_add_test(tc_core, test_prompt_for_input);
    tcase_add_test(tc_core, test_split_string_into_words);
    tcase_add_test(tc_core, test_is_negative);
    tcase_add_test(tc_core, test_cut_string_right);
    tcase_add_test(tc_core, test_cut_string_left);
    tcase_add_test(tc_core, test_contains_char);
    tcase_add_test(tc_core, test_compress_string);
    tcase_add_test(tc_core, test_filter_number_string);
    tcase_add_test(tc_core, test_word_to_double);
    tcase_add_test(tc_core, test_parse_string);
    tcase_add_test(tc_core, test_remove_char);
    tcase_add_test(tc_core, test_increase_string_size);
    tcase_add_test(tc_core, test_gcd);
    tcase_add_test(tc_core, test_is_perfect_square);
    tcase_add_test(tc_core, test_get_int_square_root);
    tcase_add_test(tc_core, test_filter_string);
    tcase_add_test(tc_core, test_read_all_input);
    tcase_add_test(tc_core, test_read_input);
    tcase_add_test(tc_core, test_read_all_input_empty);
    tcase_add_test(tc_core, test_read_input_empty);
    tcase_add_test(tc_core, test_read_all_input_long);
    tcase_add_test(tc_core, test_check_files);
    tcase_add_test(tc_core, test_read_from_file);
    tcase_add_test(tc_core, test_directory_exists);
    tcase_add_test(tc_core, test_write_to_file);
    
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
    int num_failed;
    Suite *s;
    SRunner *sr;

    s = lib_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return num_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
