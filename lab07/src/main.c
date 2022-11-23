#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gcd(int x, int y);
int** sqmat1(int k);
int main()
{
	srand(time(NULL)); //seed for rng  with an input of the currtime
	int x = 1 +rand() %6; //using it to generate first number, using +1 to get nonzero value, limiting via % because i dont want to kms looking in the outpot
	int k = x+1; //this will be matrix's dimension. useless to square matrix with a  dimension of 1, so with k=x++ it will always be >=2
	int y, gcdres, **sqmat;
	y = ((rand() % x) + rand() % (2 * x)) * ((rand() % (2 * x*x)) % 30)%(x*x+1); //generating weirdly second number for gcd
	//printf("2 GCD numbers:\n");
	//scanf("%d%d", &x,&y);
	//k = 0;
	//printf("matrix dimension will be:\n");
	//while (k < 1) {
	//	scanf("%d", &k);
	//}
	gcdres = gcd(x,y); //assigning to result the output of gcd (it will never be 0)
	printf("for %d and %d GCD is %d\n",x,y,gcdres);	
	sqmat = sqmat1(k);
	printf("squared matrix will be:\n");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d\t", sqmat[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < k; i++)
		free(sqmat[i]);
	free(sqmat);
		return 0;

}
int** sqmat1(int k)
{
	 int **mat = (int **)malloc(sizeof(int *) * k); //alloc memory for array of pointers to arrays (input)
	for (int i = 0; i < k; i++)
		mat[i] = (int *)malloc(sizeof(int)*k); //alloc memory for arrays (input)
	int **sqmat2 = (int **)malloc(sizeof(int *) * k); //alloc memory for array of pointers to arrays (output)
	for (int i = 0; i < k; i++) 
		sqmat2[i] = (int *)malloc(sizeof(int) * k); //alloc memory for arrays (output)
		printf("for input matrix with the dimension of %d and numbers\n", k);
	//for (int i = 0; i < k; i++) {
		//for (int j = 0; j < k; j++) {
			//scanf("%d",&mat[i][j]); //filling input matrix with stuff
			//printf("%d\t", mat[i][j]);
		//}
		//printf("\n");
	//}
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
			//printf("%d ", sqmat2);
		}
		//printf("\n");
	}
	for (int i=0; i < k; i++)
		free(mat[i]);
	free(mat);
	return sqmat2;
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
