#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №12.\n\tЗавдання: Визначити зворотню матрицю\n");
    srand((unsigned int)time(NULL));

    double **mat_in=NULL;
    double **mat_out=NULL;
    int size=3;
    bool randomize=true;
    int limit=11;
    int shift=-5;
    bool exist=false;
    mat_in = create_double_mat(size,randomize,limit,shift);
    mat_out = create_double_mat(size,0,0,0);
    exist=adj_reverse_mat(mat_in,mat_out,size);
    if(exist){
        print_double_mat(mat_in,size,size);
        print_double_mat(mat_out,size,size);
    }
    else{
        printf("Inverse matrix doesnt exist for this one");
    }
    destroy_mat((void**)mat_in,size);
    destroy_mat((void**)mat_out,size);    
    return 0;
}
