#include "lib.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    
printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №14 Взаємодія з файлами\n\tЗавдання: Визначити детермінант матриці якщо він існує.\n");

char* input_file = NULL;
char* output_file = strdup("./dist/output.txt");
char* text=NULL;
char* output_text = NULL;
char* errstr = strdup("Success\n");
char* mat_str = NULL;
int errcode = 0;
int shift = 2;
double* arr=NULL;
double** mat=NULL;
double det=0;
size_t arr_size=0;
size_t mat_size=0;
size_t mat_str_len = 0;
size_t prefix_len = 0;
size_t det_len = 0;
size_t total_len = 0;

switch(argc) {
    case 1:
        printf("No input file provided\nGive a file location (1 line,less then or equal to 8192 characters):\n");
        input_file=read_input_line();
        if(input_file==NULL) {
            destroy_arr((void*)errstr);
            errstr=strdup("No file provided. exiting...\n");
            errcode = -1;
            goto END;
        }
        printf("No output file destination & name provided\nDo you want to proceed with default location?(Y/N)\n");
        if(!prompt_for_input()){
            destroy_arr(output_file);
            printf("Give output file destination (1 line,less then or equal to 8192 characters):\n");
            output_file = read_input_line();
            if(output_file==NULL) {
                destroy_arr((void*)errstr);
                errstr=strdup("No destination provided or an error occured\n");
                errcode = -1;
                goto END;
            }
        }
    break;
    case 2:
        input_file=strdup(argv[1]);
        printf("No output file destination & name provided\nDo you want to proceed with default location?(Y/N)\n");
        if(!prompt_for_input()){
            destroy_arr(output_file);
            printf("Give output file destination (1 line,less then or equal to 8192 characters):\n");
            output_file = read_input_line();
            if(output_file==NULL) {
                destroy_arr((void*)errstr);
                errstr=strdup("No destination provided or an error occured\n");
                errcode = -1;
                goto END;
            }
        }
    break;
    default:
        destroy_arr(output_file);
        input_file=strdup(argv[1]);
        output_file=strdup(argv[2]);
    break;
}

if(check_files(input_file,NULL)!=0) {
    destroy_arr((void*)errstr);
    errstr=strdup("No read permission\n");
    errcode = 1;
    goto END;
}

if(check_files(NULL,output_file)!=0) {
    destroy_arr((void*)errstr);
    errstr=strdup("No write or create directory permission\n");
    errcode = 1;
    goto END;
}

read_from_file(input_file,&text);
if(text==NULL){
    destroy_arr((void*)errstr);
    errstr=strdup("Error occured while reading\n");
    errcode = 2;
    goto END;
}

if(!parse_string((const char*)text,&arr,&arr_size)) {
    destroy_arr((void*)errstr);
    errstr=strdup("Failed parsing data\n");
    errcode = 3;
    goto END;
}

if(arr_size<3) {
    destroy_arr((void*)errstr);
    errstr=strdup("Not enough data to work with\n");
    errcode = 3;
    goto END;
}

if(!(arr[0]>0&&arr[1]>0)) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions should be positive\n");
    errcode = 4;
    goto END;
}

if(fabs(fmod(arr[0], 1.0))>DBL_MIN || fabs(fmod(arr[1], 1.0))>DBL_MIN) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions are not of integer value\n");
    errcode = 4;
    goto END;
}

if((size_t)arr[0]!=(size_t)arr[1]) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix is not square\n");
    errcode = 4;
    goto END;
}

if((size_t)arr[0]*(size_t)arr[0]!=arr_size-shift) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions do not match with amount of numbers\n");
    errcode = 4;
    goto END;
}

if((size_t)arr[0]>32768 /*not actual limit but...*/ )  {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix is too big\n");
    errcode = 4;
    goto END;
}

mat=convert_array_to_mat(arr+shift,arr_size-shift,&mat_size);//pointer and size being shifted to exclude size of matrix and it's values from end matrix
det = get_determinant(mat,mat_size);

mat_str = write_double_mat_to_string(mat, mat_size, mat_size, 2);

mat_str_len=strlen(mat_str);
det_len = (size_t)snprintf(NULL, 0, "%.2f\n", det);
prefix_len = strlen("Determinant of the given matrix is: ");
total_len = det_len+prefix_len+mat_str_len+strlen("Input matrix:\n");

output_text=create_string(total_len);

sprintf(output_text,"Input matrix:\n%sDeterminant of the given matrix is: %.2f\n",mat_str,det); 

END:
switch (errcode) {
    case 0:
    printf("%s",output_text);
    write_to_file(output_file,output_text);
    break;

    case 1:
    case -1:
    printf("%s",errstr);
    break;

    default:
    printf("%s",errstr);
    write_to_file(output_file,errstr);
    break;
}
//There are checks for a nullptr inside of the memory deallocation functions. So i can make my life easier
destroy_mat((void**)mat,mat_size);
destroy_arr((void*)mat_str);
destroy_arr((void*)output_text);
destroy_arr((void*)arr);
destroy_arr((void*)text);
destroy_arr((void*)input_file);
destroy_arr((void*)output_file);
destroy_arr((void*)errstr);
return 0;
}
