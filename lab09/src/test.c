#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "lib.h"
// Include the function declaration
int **SquareMat(int **MatInput, int **MatOutput, int Size);

START_TEST(test_SquareMat)
{
	int Size = 3;
	int **MatInput = (int **)malloc(sizeof(int *) * Size);
	int **MatOutput = (int **)malloc(sizeof(int *) * Size);

	for (int i = 0; i < Size; i++) {
		MatInput[i] = (int *)malloc(sizeof(int) * Size);
		MatOutput[i] = (int *)malloc(sizeof(int) * Size);
		for (int j = 0; j < Size; j++) {
			MatInput[i][j] = i + j; /*
									 * Example input values
									 * 0 1 2
									 * 1 2 3
									 * 2 3 4
			                         */
			MatOutput[i][j] = 0; // Initialize output matrix to 0
		}
	}

	// Call the function to be tested
	int **result = SquareMat(MatInput, MatOutput, Size);

	// Perform assertions to check the result against the expected output
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			int expected = i * Size + j; // Expected output value based on the calculation
			ck_assert_int_eq(result[i][j], expected);
		}
	}

	// Clean up dynamically allocated memory
	for (int i = 0; i < Size; i++) {
		free(MatInput[i]);
		free(MatOutput[i]);
	}
	free(MatInput);
	free(MatOutput);
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

int main(void)
{
	Suite *suite = squareMat_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	int num_failures = srunner_ntests_failed(runner);
	srunner_free(runner);
	return (num_failures == 0) ? 0 : 1;
}
