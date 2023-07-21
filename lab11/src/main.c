#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    srand((unsigned int)time(NULL));

    int **mat_in=NULL;
    int *mat_out=NULL;
    int size=5;
    bool randomize=true;
    int limit=11;
    int shift=-5;

    mat_in=create_mat(size,randomize,limit,shift);
    mat_out=create_arr(size);
    mat_out=diagonal(mat_in, mat_out, size);
    bubble_sort(mat_out,size);
    destroy_arr(mat_out);
    destroy_mat(mat_in,size);

    return 0;
}
