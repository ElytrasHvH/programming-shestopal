// #include "stdio.h"
int main()
{
        int x= 3;
       // scanf("%d", &x);
        int mat1[x][x];
        int mat2[x][x];
        int i, j;
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++) {
                        mat1[i][j] = i + 2 * j * j + 1;
                }
        }
       /* for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++)
                        printf("%d ", mat1[i][j]);
                if (j == x) {
                        printf("\n");
                }
        }*/
        for (i = 0; i < x; i++) {
                for (j = 0; j < x; j++) {
                        mat2[i][j] = mat1[i][j] * mat1[j][i];
                       // printf("%d ", mat2[i][j]);
                         }
               /* if (j==x) {
                       printf("\n");
                }*/
        }
        return 0;
}
