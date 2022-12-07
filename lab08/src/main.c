/*!
\mainpage 
# Загальне завдання
Для лабораторної роботи "Функції" необхідно додати можливість генерації Doxygen документації.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*!
\brief Найбільший спільний дільник
\param int x, int y Вхідні числа для яких буде розраховуватися
\return Значення НСД
\brief Вхідні параметри псевдовипадкові(1) і користувача(2)
\code
int x = 1 +rand() %6; //using it to generate first number, using +1 to get nonzero value, limiting via % because i dont want to kms looking in the output
int y = ((rand() % x) + rand() % (2 * x)) * ((rand() % (2 * x * x)) % 30) % (x * x + 1); //generating weirdly second number for gcd

printf("2 GCD numbers:\n");
	scanf("%d%d", &x, &y);
\endcode
\brief Перевірка на тривіальне рішення
\code
if (x1 < 0) {
		x1 = -x1; //GCD for negative numbers is same as for positive, so inversing
	}
	if (y1 < 0) {
		y1 = -y1;
	}
	if (x1 == y1) {
		return x1;
	}
	if (y1 == 0) {
		return x1;
	}
	if (x1 == 0) {
		return y1;
	}
\endcode
\brief Пошук не тривіального рішення
\code
while (x1 != y1) {
		if (x1 > y1) {
			x1 -= y1;
		} else {
			y1 -= x1;
		}
	}
	return x1;
\endcode
*/
int gcd(int x, int y);
/*!
\brief Возведення матриці до квадрату
\param int k - Розмірність матриці (генерується випадково, або може буде задано користувачем)
у середині функції матриця або згенерується сама випадково, або значення можуть бути заданні користувачем
\return вказівник на масив вказівників на масив значень
\brief 2 виду заповнення матриці; перший - користувачем, другий - псевдовипадково
\code
for (int i = 0; i < k; i++) {
	for (int j = 0; j < k; j++) {
	scanf("%d",&mat[i][j]); //filling input matrix with stuff
	printf("%d\t", mat[i][j]);
	}
	printf("\n");
	}

for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			mat[i][j] = rand() % (4 + i + j); //filling input matrix with stuff
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
\endcode

\brief розрахунок матриці
\code
for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			sqmat2[i][j] = 0;
			for (int s = 0; s < k; s++) {
				sqmat2[i][j] += mat[i][s] * mat[s][j];
			}
		}
	}
\endcode

*/
int **sqmat1(int k);
/*!
основна функція
*/
int main()
{
	srand((unsigned int)time(NULL)); //seed for rng  with an input of the currtime
	int x = 1 +
		rand() %
			6; //using it to generate first number, using +1 to get nonzero value, limiting via % because i dont want to kms looking in the output
	int y = ((rand() % x) + rand() % (2 * x)) * ((rand() % (2 * x * x)) % 30) % (x * x + 1); //generating weirdly second number for gcd

	int gcdres, **sqmat;
	printf("2 GCD numbers:\n");
	scanf("%d%d", &x, &y);
	int k = x + 1; //this will be matrix's dimension.
	if (k < 2 || k > 6) {
		k = 2 + rand() % 5;
	} //useless|impossible to square matrix with dimension <2, making sure its at least 2, and limiting to 6, because it'll be too big else
	/*k = 0;
	printf("matrix dimension will be:\n");
	while (k < 1) {
		scanf("%d", &k);
	}*/
	gcdres = gcd(x, y); //gets value from functionz
	printf("for %d and %d GCD is %d\n", x, y, gcdres);
	sqmat = sqmat1(k);
	printf("squared matrix will be:\n");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d\t", sqmat[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < k; i++) {
		free(sqmat[i]);
	}
	free(sqmat);
/**Очистка пам'яті
\code
for (int i = 0; i < k; i++) {
		free(sqmat[i]);
	}
	free(sqmat);
\endcode
*/
	return 0;
}
int **sqmat1(int k)
{
	int **mat = (int **)malloc(sizeof(int *) * (unsigned long)k); //alloc memory for array of pointers to arrays (input) 
	for (int i = 0; i < k; i++) {
		mat[i] = (int *)malloc(sizeof(int) * (unsigned long)k); //alloc memory for arrays (input)
	}
	int **sqmat2 = (int **)malloc(sizeof(int *) * (unsigned long)k); //alloc memory for array of pointers to arrays (output)
	for (int i = 0; i < k; i++) {
		sqmat2[i] = (int *)malloc(sizeof(int) * (unsigned long)k); //alloc memory for arrays (output)
	}
	printf("for input matrix with the dimension of %d and numbers\n", k);
	for (int i = 0; i < k; i++) {
	for (int j = 0; j < k; j++) {
	scanf("%d",&mat[i][j]); //filling input matrix with stuff
	printf("%d\t", mat[i][j]);
	}
	printf("\n");
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			mat[i][j] = rand() % (4 + i + j); //filling input matrix with stuff
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			sqmat2[i][j] = 0;
			for (int s = 0; s < k; s++) {
				sqmat2[i][j] += mat[i][s] * mat[s][j];
			}
		}
	}
	for (int i = 0; i < k; i++) { 
		free(mat[i]);
	}
	free(mat);

	/**Очистка пам'яті
	\code
	for (int i = 0; i < k; i++) { 
		free(mat[i]);
	}
	free(mat);
	\endcode
	*/
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
	if (x1 == y1) {
		return x1;
	}
	if (y1 == 0) {
		return x1;
	}
	if (x1 == 0) {
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
