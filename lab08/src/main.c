
/*!
  \mainpage
  # Лабораторна робота №8

  \author Шестопал Дмитро:КН-922Б
  \date 07-12-22
**/
/*!
\file main.c
\brief Головний файл\n
Це файл, який містить точку входу,
виклики функцій gcd,**sqmat1 та деякі значення для аргументів цих функцій.

**/

/**
 * @brief Виконує обчислення квадратної матриці.
 *
 * @param mat_in     Вказівник на вхідну квадратну матрицю.
 * @param mat_out    Вказівник на вихідну квадратну матрицю.
 * @param size      Розмір квадратних матриць.
 * @return          Вказівник на отриману квадратну матрицю (`mat_out`).
 **/
int **square_mat(int **mat_in, int **mat_out, int size);

/**
 * @brief Обчислює найбільший спільний дільник (НСД) двох чисел.
 *
 * @param num1     Перше число.
 * @param num2     Друге число.
 * @return      НСД чисел `num1` та `num2`.
 **/
int gcd(int num1, int num2);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char **argv)
{
	int **mat_input;
	int **mat_output;
	int size = 0;
	int num1;
	int num2;
	int gcd_res;
	char buffer[100];
	char *endptr;

	srand((unsigned)time(0));
	// Generate random numbers using random()
	num1 = random() % 6;
	num2 = ((random() % (1 + 10 * num1)) + random() % (1 + 2 * num1)) * ((random() % (1 + 2 * num1 * num1 + 1)) % 30) %
	       (1 + num1 * num1 + 1); // for fun

	// Check if user has given us numbers to play with. Overwrite if yes.
	if (argc >= 4) {
		num1 = (int)strtol(argv[1], NULL, 10);
		num2 = (int)strtol(argv[2], NULL, 10);
		size = (int)strtol(argv[3], NULL, 10);
	} else if (argc == 3) {
		num1 = (int)strtol(argv[1], NULL, 10);
		num2 = (int)strtol(argv[2], NULL, 10);
	} else if (argc == 2) {
		num1 = (int)strtol(argv[1], NULL, 10);
	}

	// Get matrix dimension from user (dont ask why didnt i generate it like x and y)
	printf("Matrix dimension:\n");
	while (size < 1) {
		(void)fgets(buffer, sizeof(buffer), stdin);
		size = (int)strtol(buffer, &endptr, 10);
		if (*endptr != '\n' && *endptr != '\0') {
			printf("Invalid input. Please enter an integer.\n");
			size = 0;
		} else if (size < 1) {
			printf("Please give a correct size\n");
		}
	}

	// Allocate memory for mat_input and mat_output matrices
	mat_input = (int **)malloc(sizeof(int *) * (unsigned)size);
	mat_output = (int **)malloc(sizeof(int *) * (unsigned)size);
	for (int i = 0; i < size; i++) {
		mat_input[i] = (int *)malloc(sizeof(int) * (unsigned)size);
		mat_output[i] = (int *)malloc(sizeof(int) * (unsigned)size);
	}

	// Initialize mat_input matrix with random values and mat_output matrix with 0
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat_input[i][j] = random() % 11;
			printf("%d\t", mat_input[i][j]);
			mat_output[i][j] = 0;
		}
		printf("\n");
	}
	printf("\n");

	// Call the square_mat function to perform matrix calculations
	mat_output = square_mat(mat_input, mat_output, size);
	gcd_res = gcd(num1, num2);

	//Print the GCD
	printf("НСД у %d та %d - %d\n", num1, num2, gcd_res);
	// Print the resulting mat_output matrix
	printf("Output Matrix:\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d\t", mat_output[i][j]);
		}
		printf("\n");
	}

	// Free dynamically allocated memory
	for (int i = 0; i < size; i++) {
		free(mat_input[i]);
		free(mat_output[i]);
	}
	free(mat_input);
	free(mat_output);
	//printf("Memory has been freed successfully");
	return 0;
}

int **square_mat(int **mat_in, int **mat_out, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				// Perform multiplication and accumulate the result
				mat_out[i][j] += mat_in[i][k] * mat_in[k][j];
			}
		}
	}

	return mat_out;
}

int gcd(int num1, int num2)
{
	int num1_copy = num1;
	int num2_copy = num2;

	// Handling negative numbers
	if (num1_copy < 0) {
		num1_copy = -num1_copy; // GCD for negative numbers is the same as for positive, so we invert it
	}
	if (num2_copy < 0) {
		num2_copy = -num2_copy;
	}

	// Base cases
	if (num2_copy == 0 || num2_copy == 1 || num1_copy == num2_copy) {
		return num1_copy;
	}
	if (num1_copy == 0 || num1_copy == 1) {
		return num2_copy;
	}

	// Computing GCD using the Euclidean algorithm
	while (num1_copy != num2_copy) {
		if (num1_copy > num2_copy) {
			num1_copy -= num2_copy;
		} else {
			num2_copy -= num1_copy;
		}
	}

	return num1_copy;
}
