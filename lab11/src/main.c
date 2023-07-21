#include "lib.h"
#include <stdio.h>

int main(void){
    int **mat_in=NULL;
    int *mat_out=NULL;
    int size=5;

    mat_in=create_mat(size,1 ,10 ,5);
    mat_out=create_arr(size);
    mat_out=diagonal(mat_in, mat_out, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d\t",mat_out[i]);
    }
    printf("\n");
    bubble_sort(mat_out,size);
        for (int i = 0; i < size; i++)
    {
        printf("%d\t",mat_out[i]);
    }
    destroy_arr(mat_out);
    destroy_mat(mat_in,size);

    return 0;
}