#include "../src/lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <time.h>

START_TEST(test_mat_create_random)
{
    int size = 3;
    bool randomize = true;
    int limit = 10;
    int shift = 0;

    int **matrix = create_mat(size, randomize, limit, shift);

    // Perform assertions to check the correctness of the created matrix

    // Check that the matrix is not NULL
    ck_assert_ptr_ne(matrix, NULL);

    // Check that all elements in the matrix are within the specified limit
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ck_assert_int_ge(matrix[i][j], shift);
            ck_assert_int_lt(matrix[i][j], limit + shift);
        }
    }

    destroy_mat(matrix, size);
}
END_TEST

START_TEST(test_mat_create_not_random)
{
    int size = 3;
    bool randomize=false;
    int limit = 10;
    int shift = 0;

    int **matrix = create_mat(size, randomize, limit, shift);

    // Perform assertions to check the correctness of the created matrix

    // Check that the matrix is not NULL
    ck_assert_ptr_ne(matrix, NULL);

    // Check that all elements in the matrix are zero
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ck_assert_int_eq(matrix[i][j], 0);
        }
    }

    destroy_mat(matrix, size);
}
END_TEST

START_TEST(test_square_mat)
{
    int size = 3;
    int **mat_in = create_mat(size, false, 0, 0);
    int **mat_out = create_mat(size, false, 0, 0);

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

    destroy_mat(mat_in, size);
    destroy_mat(mat_out, size);
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
    int *arr = create_arr(size);
    ck_assert(arr != NULL);
    destroy_arr(arr);
}
END_TEST

START_TEST(test_diagonal)
{
    int size = 3;
    int **mat_in = create_mat(size, false, 0, 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat_in[i][j] = i * size + j;
        }
    }
    int *arr = create_arr(size);
    arr = diagonal(mat_in, arr, size);
    ck_assert_int_eq(arr[0], 0);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 8);
    destroy_arr(arr);
    destroy_mat(mat_in, size);
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

//Test RNG with positive limit value
START_TEST(test_generate_random_value_positive_limit)
{
    int limit = 10;
    int shift = 5;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        int value = generate_random_value(limit, shift);
        ck_assert_int_ge(value, shift);
        ck_assert_int_lt(value, limit + shift);
    }
}
END_TEST

//Test RNG with negative limit value
START_TEST(test_generate_random_value_negative_limit)
{
    int limit = -10;
    int shift = 5;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        int value = generate_random_value(limit, shift);
        ck_assert_int_ge(value, -abs(limit) + shift);
        ck_assert_int_le(value, shift);
    }
}
END_TEST

//Test RNG with 0 limit value
START_TEST(test_generate_random_value_zero_limit)
{
    int limit = 0;
    int shift = 5;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        int value = generate_random_value(limit, shift);
        ck_assert_int_ge(value, shift);
        ck_assert_int_le(value, INT_MAX);
    }
}
END_TEST


Suite *lib_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Lib");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_mat_create_random);
    tcase_add_test(tc_core, test_mat_create_not_random);
    tcase_add_test(tc_core, test_square_mat);
    tcase_add_test(tc_core, test_gcd);
    tcase_add_test(tc_core, test_create_arr);
    tcase_add_test(tc_core, test_diagonal);
    tcase_add_test(tc_core, test_bubble_sort);
    tcase_add_test(tc_core, test_generate_random_value_positive_limit);
    tcase_add_test(tc_core, test_generate_random_value_negative_limit);
    tcase_add_test(tc_core, test_generate_random_value_zero_limit);
    
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
