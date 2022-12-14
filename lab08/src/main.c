/*!
  \mainpage
  # Лабораторна робота №8
 
  \author Шестопал Дмитро:КН-922Б
  \date 07-12-20
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 /*!
\file main.c
\brief Головний файл\n
Це файл, який містить точку входу,
виклики функцій gcd,**sqmat1 та деякі значення для аргументів цих функцій.

*/
/*!
\briefНСД (Найбільший Спільний Дільник)

\param x1 дорівнює значенню x який було передано функції (локальна змінна)
\param y1 дорівнює значееню y який було передано функції (локальна змінна)

-Перевірка на від'ємність обох чисел, якщо число від'ємне - інветуємо

-Перевірки на тривіальні рішення (число дорівнюють один одному, 1 число 0 або 1)

-Якщо не було знайдено такого числа то пошук НСД
\return x1 який є НСД x та y
*/
int gcd(int x, int y);
/*!
\brief Піднесення матриці до квадрату

\param k Єдиний параметр котрий передається у функцію, є розміром матриці

- \param**mat - вказівник на массив вказівників на массиви значень, вхідна матриця

- \param**sqmat2 - вказівник на массив вказівників на массиви значень, матриця яка буде приймати результат

- За допомогою scanf або псевдовипадкової генерації чисел rand() mat[k][k] приймає значення чисел з яких состоїть матриця

\return вказівник на массив массивів
*/
int **sqmat1(int k);

/*!
Основна функція
\brief Є точкою входу там має визови функцій **sqmat1 та gcd

\param x Перше число для якого розраховувати НСД може бути задано користувачем або зегенроване само
\param y Друге число для якого розраховувати НСД може бути задано користувачем або зегенроване само
\param k Розмір матриці
\param gcdres Змінна який призначається значення з функії gcd
\param **sqmat Вказівник на який виклакається функція множення матриць


*/
int main(int argc,char **argv)
{
	int x, y, k, gcdres, **sqmat;
	srand((unsigned int)time(NULL));
	x = (rand() % 6);
	y = ((rand() % (1 + 10 * x)) + rand() % (1 + 2 * x)) * ((rand() % (1 + 2 * x * x + 1)) % 30) % (1 + x * x + 1);
	k = (2 + rand() % 9); //This is matrix's dimension. Generated and locked to 10, otherwise its too big to see	
	if(argc==2) {
	x=atoi(argv[1]);
	} 
	else if(argc>2) {
	x=atoi(argv[1]);
	y=atoi(argv[2]);	
	}
	/*k = 0;
	printf("Set matrix dimension (Only > 1 allowed):\n");
	while (k < 1) {
		scanf("%d", &k);
	}*/
	gcdres = gcd(x, y); //call for function to find GCD
	//printf("GCD of %d and %d is %d\n", x, y, gcdres);
	sqmat = sqmat1(k); //call for function to get matrix
	/*printf("squared matrix will be:\n");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d\t", sqmat[i][j]);
		}
		printf("\n");
	}*/
	for (int i = 0; i < k; i++) {
		free(sqmat[i]);
	}
	free(sqmat);

	return 0;

}
int **sqmat1(int k)
{
	int **mat;
	int **sqmat2;
	mat = (int **)malloc(sizeof(int *) * (unsigned long)k); //alloc memory for array of pointers to arrays (input)
	sqmat2 = (int **)malloc(sizeof(int *) * (unsigned long)k); //alloc memory for array of pointers to arrays (output)
	for (int i = 0; i < k; i++) {
		mat[i] = (int *)malloc(sizeof(int) * (unsigned long)k); //alloc memory for arrays (input)
		sqmat2[i] = (int *)malloc(sizeof(int) * (unsigned long)k); //alloc memory for arrays (output)
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			mat[i][j] = rand() % (4 + i + j); //filling input matrix with random numbers
			sqmat2[i][j] = 0;
			//printf("%d\t", mat[i][j]);
		}
		//printf("\n");
	}
	/*printf("Write your numbers for square matrix with the size of %d\n", k);
	for (int i = 0; i < k; i++) {
	for (int j = 0; j < k; j++) {
	scanf("%d",&mat[i][j]); //filling input matrix with stuff
	}*/
	
	/*printf("This is Your matrix\n");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}*/

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			for (int s = 0; s < k; s++) {
				sqmat2[i][j] += mat[i][s] * mat[s][j];
			}
		}
	}
	for (int i = 0; i < k; i++) { 
		free(mat[i]);
	}
	free(mat);

	return sqmat2;
}
int gcd(int x, int y)
{
	int x1 = x;
	int y1 = y;
	if (x1 < 0) {
		x1 = -x1; //GCD for negative numbers is same as for positive, so inversing
	}
	if (y1 < 0) {
		y1 = -y1;
	}
	if (y1 == 0||y1==1||x1==y1) {
		return x1;
	}
	if (x1 == 0||x1==1) {
		return y1;
	}
	while (x1 != y1) {
		if (x1 > y1) {
			x1 -= y1;
		} else {
			y1 -= x1;
		}
	}
	return x1;
}
