#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gcd(int x, int y);
int **sqmat1(int k);
int main()
{
	srand(time(NULL)); //seed for rng  with an input of the currtime
	int x = 1 +
		rand() %
			6; //using it to generate first number, using +1 to get nonzero value, limiting via % because i dont want to kms looking in the outpot
	int y, gcdres, **sqmat, **mat;
	int k = x + 1; //this will be matrix's dimension. useless to square matrix with a  dimension of 1, so with k=x++ it will always be >=2
	y = rand() % x; //generating weirdly
	y += rand() % (x + x); //second number
	y *= ((rand() % (x + x) * x) % 30) + 1; //for gcd
	gcdres = gcd(
		x,
		y); //assigning to result the output of gcd (fun fact, it will never be 0 with above inputs and also the only moment when x can be equal to y is when x is 1)
	sqmat = **sqmat1(k);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d ", sqmat[i][j]);
		}
		printf("\n");
	}
	printf("%d %d", gcdres, sqmat);
	return 0;
}
int **sqmat1(int k)
{
	int **mat;
	int **sqmat1;

	mat = malloc(sizeof(int *) * k);
	sqmat1 = malloc(sizeof(int *) * k);

	for (int i = 0; i < k; i++) {
		mat[i] = malloc(sizeof(int *) * k);
		sqmat1[i] = malloc(sizeof(int *) * k);
	};
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			mat[i][j] = rand() % (4 + i + j);
			sqmat1[i][j] = mat[i][j];
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

	return sqmat1;
}
int gcd(int x, int y)
{
	int x1 = x;
	int y1 = y;
	while (x1 != y1) {
		if (x1 == 0) {
			if (y1 > 0)
				x1 = y1;
			else
				x1 = -y1;
		} else if (y1 == 0) { //This all made for calculating gcd while one or both numbers are 0
			if (x1 > 0) //Also GCD is alway1s >0 so made inverses to fix1 when one of numbers is 0 and other is negative
				y1 = x1;
			else
				x1 = -x1;
		} else if (x1 == 0 && y1 == 0) {
			return 0;
		} else if (x1 > y1) // check if first number is bigger then second
		{
			if (y1 > 0) { //check if second number is positive
				x1 -= y1;
			} else // inversing number coz GCD will be same for them being positive
			{
				y1 = -y1;
			}
		} else // we know that y1>x1 and that x1!=0 && y1!=0 so this then
		{
			if (x1 > 0) //check if x1 positive
			{
				y1 -= x1;
			} else //same as before
			{
				x1 = -x1;
			}
		}
	}
	return x1;
}