/*!
  \mainpage
  # Лабораторна робота №8

  \author Шестопал Дмитро:КН-922Б
  \date 07-12-22
 */
/*!
\file main.c
\brief Головний файл\n
Це файл, який містить точку входу,
виклики функцій gcd,**sqmat1 та деякі значення для аргументів цих функцій.

*/

/*!
Основна функція
\brief Є точкою входу там має визови функцій **sqmat1 та gcd

\param x Перше число для якого розраховувати НСД може бути задано користувачем або зегенроване само
\param y Друге число для якого розраховувати НСД може бути задано користувачем або зегенроване само
\param Size Розмір матриці
\param GCDres Отримає НСД між x та y від GCDres
\param **sqmat Вказівник на який виклакається функція множення матриць


*/

/**
 * @brief Основна функція програми.
 * @return Код виходу з програми.
 */
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int **mat_input;
	int **mat_output;
	int size = 0;
	int numfrst;
	int numscnd;
	int gcd_res;

	// Generate random numbers using random()
	numfrst = random() % 6;
	numscnd = ((random() % (1 + 10 * numfrst)) + random() % (1 + 2 * numfrst)) * ((random() % (1 + 2 * numfrst * numfrst + 1)) % 30) %
		  (1 + numfrst * numfrst + 1); // for fun

	// Check if user has given us numbers to play with. Overwrite if yes.
	if (argc >= 4) {
		numfrst = (int)strtol(argv[1], NULL, 10);
		numscnd = (int)strtol(argv[2], NULL, 10);
		size = (int)strtol(argv[3], NULL, 10);
	} else if (argc == 3) {
		numfrst = (int)strtol(argv[1], NULL, 10);
		numscnd = (int)strtol(argv[2], NULL, 10);
	} else if (argc == 2) {
		numfrst = (int)strtol(argv[1], NULL, 10);
	}

	// Get matrix dimension from user
	printf("Matrix dimension:\n");
	char buffer[100];
	(void)fgets(buffer, sizeof(buffer), stdin);
	size = (int)strtol(buffer, NULL, 10);
	while (size < 1) {
		printf("Please enter a correct size\n");
		(void)fgets(buffer, sizeof(buffer), stdin);
		size = (int)strtol(buffer, NULL, 10);
	}

	// Allocate memory for MatInput and MatOutput matrices
	mat_input = (int **)malloc(sizeof(int *) * (unsigned int)size);
	mat_output = (int **)malloc(sizeof(int *) * (unsigned int)size);
	for (int i = 0; i < size; i++) {
		mat_input[i] = (int *)malloc(sizeof(int) * (unsigned int)size);
		mat_output[i] = (int *)malloc(sizeof(int) * (unsigned int)size);
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

	// Call the SquareMat function to perform matrix calculations
	mat_output = SquareMat(mat_input, mat_output, size);
	gcd_res = gcd(numfrst, numscnd);

	// Print the GCD
	printf("НСД у %d та %d - %d\n", numfrst, numscnd, gcd_res);

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

	return 0;
}

//for anyone reading this. i tryied to kms 15 times trying to make unit test via libcheck for this.
