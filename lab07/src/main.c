#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int sqmat(int k);
int gcd(int x, int y);
int main()
{
	srand(time(NULL)); //seed for rng  with an input of the currtime
	int x = 1 +rand()%6; //using it to generate first number, using +1 to get nonzero value, limiting via % because i dont want to kms looking in the outpot
	int y;
	int gcdres; //this will be the result for gcd
	int k = x + 1; //this will be matrix's dimension. useless to square matrix with a  dimension of 1, so with k=x++ it will always be >=2
	int mat[k]; //output matrix
	y = rand() % x; //generating weirdly
	y += rand() % (x + x); //second
	y *= ((rand() % (x + x) * x) % 30) + 1; //number
	gcdres = gcd(
		x,
		y); //assigning to result the output of gcd (fun fact, it will never be 0 with above inputs and also the only moment when x can be equal to y is when x is 1)
	printf("For numbers:%d %d \ngcd is: %d \nfor matrix with a dimension of %d\nwith numbers:\n", x, y, gcdres, k);
	k=sqmat(k);
	return 0;
}

int sqmat(int k)
{
	int mat[k][k];
	int kk = k*k;
	int mat2[kk];
	int mat3[k][k];
	mat3[0][0]=0;
	for (int i = 0; i < k; i++) {					  //filling matrix (row)
		for (int j = 0; j < k; j++) {				  //like this (column)
			mat[i][j] = (rand() % (i * j + 3)) % (i + j + 3); //because i like chaos
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d ", mat[i][j]);
		}
	printf("\n");
	}
	for (int i = 0; i < k; i++) { //for every row
		for (int j = 0; j < k; j++) { //and every column
			for (int s = 0; s < k; k++) { //s being a counter to get numbers with a look of number(column's number) and (row's number)number
				mat3[i][j] += mat[i][s] * mat[s][j]; //adding up because this how matrix multiplication works
			}
		}
	return;
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
