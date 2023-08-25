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
char* errstr = NULL;
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

handle_args(argc, argv, &input_file, &output_file, &errstr, &errcode);
while(errcode==0){
if(check_files(input_file,NULL)!=0) {
    destroy_arr((void*)errstr);
    errstr=strdup("No read permission\n");
    errcode = 1;
    break;
}

if(check_files(NULL,output_file)!=0) {
    destroy_arr((void*)errstr);
    errstr=strdup("No write or create directory permission\n");
    errcode = 1;
    break;
}

read_from_file(input_file,&text);

if(text==NULL) {
    destroy_arr((void*)errstr);
    errstr=strdup("Error occured while reading\n");
    errcode = 2;
    break;
}

if(!parse_string((const char*)text,&arr,&arr_size)) {
    destroy_arr((void*)errstr);
    errstr=strdup("Failed parsing data\n");
    errcode = 3;
    break;
}
if(arr_size<3) {
    destroy_arr((void*)errstr);
    errstr=strdup("Not enough data to work with\n");
    errcode = 3;
    break;
}

if(!(arr[0]>0&&arr[1]>0)) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions should be positive\n");
    errcode = 4;
    break;
}

if(fabs(fmod(arr[0], 1.0))>DBL_MIN || fabs(fmod(arr[1], 1.0))>DBL_MIN) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions are not of integer value\n");
    errcode = 4;
    break;
}

if((size_t)arr[0]!=(size_t)arr[1]) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix is not square\n");
    errcode = 4;
    break;
}

if((size_t)arr[0]*(size_t)arr[0]!=arr_size-(size_t)shift) {
    destroy_arr((void*)errstr);
    errstr=strdup("Matrix dimensions do not match with amount of numbers\n");
    errcode = 4;
    break;
}
break;
}

handle_output(output_text, output_file, errstr, errcode);

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
