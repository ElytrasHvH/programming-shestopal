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
#include "lib.h"
#include "lib.c"

int main(int argc, char **argv)
{
	int **MatInput, **MatOutput, Size = 0, x, y, GCDres;
	srand((unsigned)time(0));
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
	MatInput = (int **)malloc(sizeof(int *) * (unsigned int)Size);
	MatOutput = (int **)malloc(sizeof(int *) * (unsigned int)Size);
	for (int i = 0; i < Size; i++) {
		MatInput[i] = (int *)malloc(sizeof(int) * (unsigned int)Size);
		MatOutput[i] = (int *)malloc(sizeof(int) * (unsigned int)Size);
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




//for anyone reading this. i tryied to kms 15 times trying to make unit test via libcheck for this.
