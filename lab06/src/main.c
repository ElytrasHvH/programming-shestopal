#include "stdio.h"
int main()
{

        int x;
        printf("Matrix dimenion is: ");
        scanf("%d", &x);
        int i,j,k, a[x][x], b[x][x];
        printf("\n");
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++) {
                        a[i][j] = (i+1)*j+i;
                }
        }
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++)
                        printf("%d ", a[i][j]);
                if (j == x) {
                        printf("\n");
                }
        }
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++) {
                        b[i][j] = 0;
                        for (k = 0; k < x; k++) {
                                b[i][j] += a[i][k] * a[k][j];
                        }
                }
        }
        for (i=0;i<x;i++) {
            for (j = 0; j<n; j++)
return 0;
}

