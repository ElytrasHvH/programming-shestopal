#include "../src/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <check.h>


START_TEST(test_SquareMat)
{
	int size = 3;
	int **mat_input = (int **)malloc(sizeof(int *) * (unsigned int)size);
	int **mat_output = (int **)malloc(sizeof(int *) * (unsigned int)size);

	for (int i = 0; i < size; i++) {
		mat_input[i] = (int *)malloc(sizeof(int) * (unsigned int)size);
		mat_output[i] = (int *)malloc(sizeof(int) * (unsigned int)size);
		for (int j = 0; j < size; j++) {
			mat_input[i][j] = i + j; /*
									 * Example input values
									 * 0 1 2
									 * 1 2 3
									 * 2 3 4
			                         */
			mat_output[i][j] = 0; // Initialize output matrix to 0
		}
	}

		//Expected values
    int expected[3][3] = {
        {5, 8, 11},
        {8, 14, 20},
        {11, 20, 29}
    };

	// Call the function to be tested
	int **result = SquareMat(mat_input, mat_output, size);

	// Perform assertions to check the result against the expected output
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			ck_assert_int_eq(result[i][j], expected[i][j]);
		}
	}

	// Clean up dynamically allocated memory
	for (int i = 0; i < size; i++) {
		free(mat_input[i]);
		free(mat_output[i]);
	}
	free(mat_input);
	free(mat_output);
}
END_TEST

START_TEST(test_gcd)
{
    int num1 = 10;
    int num2 = 15;
    int expected_result = 5;
    int result = gcd(num1, num2);
    ck_assert_int_eq(result, expected_result);
}
END_TEST

Suite *squareMat_suite(void)
{
	Suite *suite = suite_create("SquareMat");
	TCase *tcase = tcase_create("Core");
	tcase_add_test(tcase, test_SquareMat);
	suite_add_tcase(suite, tcase);
	return suite;
}

Suite *gcd_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GCD");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_gcd);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    Suite *squareMatSuite = squareMat_suite();
    Suite *gcdSuite = gcd_suite();

    SRunner *runner = srunner_create(squareMatSuite);
    srunner_add_suite(runner, gcdSuite);

    srunner_run_all(runner, CK_NORMAL);
    int num_failures = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (num_failures == 0) ? 0 : 1;
}
