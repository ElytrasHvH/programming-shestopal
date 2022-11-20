#include <stdio.h>
int main()
{
	int x = -1;
	int ii;
	for (ii = 0; x < 1; ii++) { //kinda infinite loop forcing to make matrix's dimenson positive integer
		printf("Matrix dimension is: ");
		scanf("%d", &x);
		if (x < 1) {
			printf("Dimension must be at least 1\n");
		}
	}
	int k, j, i, a[x][x], b[x][x];
	printf("\n");
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			a[i][j] = (i + 1) * j + i; //filling matrix with random stuff
		}
	}
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			printf("%d ", a[i][j]); //printing matrix that was computed (before squaring)
		}
		if (j == x) {
			printf("\n"); //dropping to next line to see matrix normally
		}
	}
	for (i = 0; i < x; i++) { //for every row
		for (j = 0; j < x; j++) { //and every column
			b[0][0] = 0;
			for (k = 0; k < x; k++) { //k being a counter to get numbers with a look of number(column's number) and (row's number)number
				b[i][j] += a[i][k] * a[k][j]; //adding up because this how matrix multiplication works
			}
		}
	}
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			printf("%d ", b[i][j]); //printing matrix that was computed (after squaring)
		}
		if (j == x) {
			printf("\n"); //dropping to next line to see matrix normally
		}
	}
	return 0;
}
