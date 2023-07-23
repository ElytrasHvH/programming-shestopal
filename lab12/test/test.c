#include "../src/lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define EPSILON 0.00001

START_TEST(test_create_int_mat_not_random)
{
    int size = 3;
    int limit = 10;
    int shift = 0;
    int **mat = create_int_mat(size, false, limit, shift);
    ck_assert(mat != NULL);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ck_assert_int_eq(mat[i][j], 0);
        }
    }
    destroy_mat((void**)mat, size);
}
END_TEST

START_TEST(test_create_double_mat_not_random)
{
    int size = 3;
    double limit = 10.0;
    double shift = 0.0;
    double **mat = create_double_mat(size, false, limit, shift);
    ck_assert(mat != NULL);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ck_assert(fabs(mat[i][j] - 0.0) < EPSILON);
        }
    }
    destroy_mat((void**)mat, size);
}
END_TEST
START_TEST(test_create_int_mat_random)
{
    int size = 3;
    int limit = 10;
    int shift = 0;
    int **mat = create_int_mat(size, true, limit, shift);
    ck_assert(mat != NULL);
    destroy_mat((void**)mat, size);
}
END_TEST

START_TEST(test_create_double_mat_random)
{
    int size = 3;
    double limit = 10.0;
    double shift = 0.0;
    double **mat = create_double_mat(size, true, limit, shift);
    ck_assert(mat != NULL);
    destroy_mat((void**)mat, size);
}
END_TEST


START_TEST(test_generate_random_int_value_positive_limit)
{
    int limit = 10;
    int shift = 0;
    int value = generate_random_int_value(limit, shift);
    ck_assert(value >= 0 && value <= limit);
}
END_TEST

START_TEST(test_generate_random_int_value_negative_limit)
{
    int limit = -10;
    int shift = 0;
    int value = generate_random_int_value(limit, shift);
    ck_assert(value >= limit && value <= 0);
}
END_TEST

START_TEST(test_generate_random_int_value_zero_limit)
{
    int limit = 0;
    int shift = 0;
    int value = generate_random_int_value(limit, shift);
    ck_assert(value >= INT_MIN && value <= INT_MAX);
}
END_TEST

START_TEST(test_generate_random_double_value_positive_limit)
{
    double limit = 10.0;
    double shift = 0.0;
    double value = generate_random_double_value(limit, shift);
    ck_assert(value >= 0.0 && value <= limit);
}
END_TEST

START_TEST(test_generate_random_double_value_negative_limit)
{
    double limit = -10.0;
    double shift = 0.0;
    double value = generate_random_double_value(limit, shift);
    ck_assert(value >= limit && value <= 0.0);
}
END_TEST

START_TEST(test_generate_random_double_value_zero_limit)
{
   double limit = 0.0;
   double shift = 0.0;
   double value = generate_random_double_value(limit, shift);
   ck_assert(value >= 0.0 && value <= 1.0);
}
END_TEST


START_TEST(test_square_mat)
{
    int size = 3;
    int **mat_in = create_int_mat(size, false, 0, 0);
    int **mat_out = create_int_mat(size, false, 0, 0);

    // Fill mat_in with i+k values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat_in[i][j] = i + j;
        }
    }

    square_mat(mat_in, mat_out, size);

    // Perform assertions to check the correctness of the squared matrix

    ck_assert_int_eq(mat_out[0][0], 5);
    ck_assert_int_eq(mat_out[0][1], 8);
    ck_assert_int_eq(mat_out[0][2], 11);
    ck_assert_int_eq(mat_out[1][0], 8);
    ck_assert_int_eq(mat_out[1][1], 14);
    ck_assert_int_eq(mat_out[1][2], 20);
    ck_assert_int_eq(mat_out[2][0], 11);
    ck_assert_int_eq(mat_out[2][1], 20);
    ck_assert_int_eq(mat_out[2][2], 29);

    destroy_mat((void**)mat_in, size);
    destroy_mat((void**)mat_out, size);
}
END_TEST

START_TEST(test_gcd)
{
    int num1 = 12;
    int num2 = 18;
    int expected_gcd = 6;

    int result = gcd(num1, num2);

    ck_assert_int_eq(result, expected_gcd);
}
END_TEST
START_TEST(test_create_arr)
{
    int size = 5;
    int *arr = create_int_arr(size);
    ck_assert(arr != NULL);
    destroy_arr((void*)arr);
}
END_TEST

START_TEST(test_diagonal)
{
    int size = 3;
    double **mat_in = create_double_mat(size, false, 0, 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat_in[i][j] = i * size + j;
        }
    }

    double *arr = create_double_arr(size);
    arr = diagonal(mat_in, arr, size);

    ck_assert_int_eq((int)arr[0], 0);
    ck_assert_int_eq((int)arr[1], 4);
    ck_assert_int_eq((int)arr[2], 8);

    destroy_arr((void*)arr);
    destroy_mat((void**)mat_in, size);
}
END_TEST

START_TEST(test_bubble_sort)
{
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, size);
    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 2);
    ck_assert_int_eq(arr[2], 3);
    ck_assert_int_eq(arr[3], 4);
    ck_assert_int_eq(arr[4], 5);
}
END_TEST

//Test determinant calucalation function
START_TEST(test_get_determinant)
{
    int size = 3;
    double **mat = create_double_mat(size, true, 3, 3);

    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 7;
    mat[2][1] = 8;
    mat[2][2] = 9;

    int det = (int)get_determinant(mat, size);

    ck_assert_int_eq(det, 0);

    destroy_mat((void**)mat, size);
}
END_TEST
//Test cofactor calculation
START_TEST(test_get_cofactor)
{
    int size = 3;
    double **mat = create_double_mat(size, 0, 0, 0);
    double **temp = create_double_mat(size - 1, false, 0, 0);

    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 7;
    mat[2][1] = 8;
    mat[2][2] = 9;

    get_cofactor(mat, temp, 0, 0, size);

    ck_assert_double_eq_tol(temp[0][0], 5, EPSILON);
    ck_assert_double_eq_tol(temp[0][1], 6, EPSILON);
    ck_assert_double_eq_tol(temp[1][0], 8, EPSILON);
    ck_assert_double_eq_tol(temp[1][1], 9, EPSILON);

    destroy_mat((void**)mat, size);
    destroy_mat((void**)temp, size - 1);
}
END_TEST
//Test calculation of adjugate matrix
START_TEST(test_get_adj_matrix)
{
    int size = 3;
    double **mat = create_double_mat(size, false, 0, 0);
    double **adj = create_double_mat(size, false, 0, 0);

    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 7;
    mat[2][1] = 8;
    mat[2][2] = 9;

    get_adj_matrix(mat, adj, size);

    ck_assert_double_eq_tol(adj[0][0], -3, EPSILON);
    ck_assert_double_eq_tol(adj[0][1], 6, EPSILON);
    ck_assert_double_eq_tol(adj[0][2], -3, EPSILON);
    ck_assert_double_eq_tol(adj[1][0], 6, EPSILON);
    ck_assert_double_eq_tol(adj[1][1], -12, EPSILON);
    ck_assert_double_eq_tol(adj[1][2], 6, EPSILON);
    ck_assert_double_eq_tol(adj[2][0], -3, EPSILON);
    ck_assert_double_eq_tol(adj[2][1], 6, EPSILON);
    ck_assert_double_eq_tol(adj[2][2], -3, EPSILON);

    destroy_mat((void**)mat, size);
    destroy_mat((void**)adj, size);
}
END_TEST

START_TEST(test_swap_rows) {
    double a[2] = {1.0, 2.0};
    double b[2] = {3.0, 4.0};
    double *mat[2] = {a, b};

    swap_rows((void **)mat, 0, 1);

    ck_assert(fabs(mat[0][0] - 3.0) < EPSILON);
    ck_assert(fabs(mat[0][1] - 4.0) < EPSILON);
    ck_assert(fabs(mat[1][0] - 1.0) < EPSILON);
    ck_assert(fabs(mat[1][1] - 2.0) < EPSILON);
}
END_TEST

Suite *lib_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Lib");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_int_mat_random);
    tcase_add_test(tc_core, test_create_int_mat_not_random);
    tcase_add_test(tc_core, test_create_double_mat_random);
    tcase_add_test(tc_core, test_create_double_mat_not_random);

    tcase_add_test(tc_core, test_generate_random_int_value_positive_limit); 
    tcase_add_test(tc_core, test_generate_random_int_value_negative_limit); 
    tcase_add_test(tc_core, test_generate_random_int_value_zero_limit); 
    
    tcase_add_test(tc_core,test_generate_random_double_value_positive_limit); 
    tcase_add_test(tc_core,test_generate_random_double_value_negative_limit); 
    tcase_add_test(tc_core,test_generate_random_double_value_zero_limit); 
    tcase_add_test(tc_core, test_get_determinant);
    tcase_add_test(tc_core, test_get_cofactor);
    tcase_add_test(tc_core, test_get_adj_matrix);
    tcase_add_test(tc_core, test_bubble_sort);
    tcase_add_test(tc_core, test_square_mat);
    tcase_add_test(tc_core, test_gcd);
    tcase_add_test(tc_core, test_create_arr);
    tcase_add_test(tc_core, test_diagonal);
    tcase_add_test(tc_core, test_swap_rows);
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
