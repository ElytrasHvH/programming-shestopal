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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * @file lib.h
 * @brief Заголовочний файл з прототипами функцій для обчислення квадратної матриці та функції НСД.
 */


/**
 * @brief Виконує обчислення квадратної матриці.
 *
 * @param MatIn     Вказівник на вхідну квадратну матрицю.
 * @param MatOut    Вказівник на вихідну квадратну матрицю.
 * @param size      Розмір квадратних матриць.
 * @return          Вказівник на отриману квадратну матрицю (`MatOut`).
 */
int **SquareMat(int **MatIn, int **MatOut, int size);

/**
 * @brief Обчислює найбільший спільний дільник (НСД) двох чисел.
 *
 * @param x     Перше число.
 * @param y     Друге число.
 * @return      НСД чисел `x` та `y`.
 */
int gcd(int x, int y);



int main(int argc, char **argv)
{
	int **MatInput, **MatOutput, Size = 0, x, y, GCDres;
	srand(time(0));
	//Generate first, check later
	x = rand() % 6;
	y = ((rand() % (1 + 10 * x)) + rand() % (1 + 2 * x)) * ((rand() % (1 + 2 * x * x + 1)) % 30) % (1 + x * x + 1); //for fun

	//Check if user has given us a numbers to play with. overwrite if yes.
	if (argc >= 4) {
		x = atoi(argv[1]);
		y = atoi(argv[2]);
		Size = atoi(argv[3]);

	} else if (argc == 3) {
		x = atoi(argv[1]);
		y = atoi(argv[2]);
	} else if (argc == 2)
		x = atoi(argv[1]);

	// Get matrix dimension from user (dont ask why didnt i generate it like x and y)
	printf("Matrix dimension:\n");
	while (Size < 1) {
		scanf("%d", &Size);
		if (Size < 1)
			printf("Please give a correct size");
	}

	// Allocate memory for MatInput and MatOutput matrices
	MatInput = (int **)malloc(sizeof(int *) * Size);
	MatOutput = (int **)malloc(sizeof(int *) * Size);
	for (int i = 0; i < Size; i++) {
		MatInput[i] = (int *)malloc(sizeof(int) * Size);
		MatOutput[i] = (int *)malloc(sizeof(int) * Size);
	}

	// Initialize MatInput matrix with random values and MatOutput matrix with 0
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			MatInput[i][j] = rand() % 11;
			printf("%d\t", MatInput[i][j]);
			MatOutput[i][j] = 0;
		}
		printf("\n");
	}
	printf("\n");

	// Call the SquareMat function to perform matrix calculations
	MatOutput = SquareMat(MatInput, MatOutput, Size);
	GCDres = gcd(x, y);

	//Print the GCD
	printf("НСД у %d та %d - %d\n", x, y, GCDres);
	// Print the resulting MatOutput matrix
	printf("Output Matrix:\n");
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			printf("%d\t", MatOutput[i][j]);
		}
		printf("\n");
	}

	// Free dynamically allocated memory
	for (int i = 0; i < Size; i++) {
		free(MatInput[i]);
		free(MatOutput[i]);
	}
	free(MatInput);
	free(MatOutput);
	//printf("Memory has been freed successfully");
	return 0;
}


#include "lib.h"

int **SquareMat(int **MatIn, int **MatOut, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int s = 0; s < size; s++) {
				// Perform multiplication and accumulate the result
				MatOut[i][j] += MatIn[i][s] * MatIn[s][j];
			}
		}
	}

	return MatOut;
}

int gcd(int x, int y)
{
	int x1 = x;
	int y1 = y;

	// Handling negative numbers
	if (x1 < 0) {
		x1 = -x1; // GCD for negative numbers is the same as for positive, so we invert it
	}
	if (y1 < 0) {
		y1 = -y1;
	}

	// Base cases
	if (y1 == 0 || y1 == 1 || x1 == y1) {
		return x1;
	}
	if (x1 == 0 || x1 == 1) {
		return y1;
	}

	// Computing GCD using the Euclidean algorithm
	while (x1 != y1) {
		if (x1 > y1) {
			x1 -= y1;
		} else {
			y1 -= x1;
		}
	}

	return x1;
}


