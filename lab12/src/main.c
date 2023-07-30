#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    //printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №12.\n\tЗавдання: Визначити зворотню матрицю\n");
    srand((unsigned int)time(NULL));

    bool exist_inverse_mat = false;
    bool exist_arr = false;
    bool filled = false;
    size_t count = 0;
    size_t size_mat=0;
    size_t size_arr = 0;
    double* *mat_in = NULL;
    double** mat_out = NULL;
    double* arr=create_double_arr(size_arr);
    int precision = 2;
    char* str=read_input(stdin,&count,&filled);
    if(*str==0 && count == 0){
        printf("Invalid stream");
        return 0;
    }
    if(count!=0){
        printf("Do you want to give a matrix? (y/n)\n");
        if(prompt_for_input(stdin));
        printf("Send a matrix in 1 line\n");
        str=read_input(stdin,&count,&filled);
    }

    mat_out = create_double_mat(size_mat, 0, 0, 0);

    //
    //TODO: calculations and checks
    //
    destroy_mat((void**)mat_out, size_mat); 
    destroy_arr((void*)arr);
    destroy_arr((void*)str);

    return 0;
}
