#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
 printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №12.\n\tЗавдання: Визначити зворотню матрицю\n");
 srand((unsigned int)time(NULL));

 size_t size_mat = 0;
 size_t size_arr = 0;
 printf("Give 1 line string of numbers to fill an array.\n");
 char* str = read_input();
 if (str == NULL) {
  printf("No input given, do you want to proceed? (y/n)\n");
  if (prompt_for_input()) {
   str = read_input();
   printf("Give 1 line string of numbers to fill an array.\n");
   if (str == NULL) {
    printf("Empty string or failed to read\n");
    return 0;
   }
  } else {
   return 0;
  }
 }

 double* arr = NULL;
 double** mat_in = NULL;
 double** mat_out = NULL;
 int prec = 2;
 if (parse_string(str, &arr, &size_arr) == false) {
  printf("Nothing was in the string\n");
  destroy_arr((void*)str);
  destroy_arr((void*)arr);
  return 0;
 }
 mat_in = convert_array_to_mat(arr, size_arr, &size_mat);
 mat_out = create_double_mat(size_mat, 0, 0, 0);

 if (is_perfect_square((int)size_arr)) {
  printf("Your matrix:\n");
  print_double_mat(mat_in, size_mat, size_mat, prec);

  if(inverse_mat(mat_in, mat_out, size_mat)){
   printf("Inverse matrix:\n");
   print_double_mat(mat_out, size_mat, size_mat, prec);
  } else {
   printf("Inverse matrix doesn't exist\n");
  }
 } else {
  printf("Amount of numbers is not a perfect square.\nCan't create a 2d matrix.\nHere what closest one looks like:\n");
  print_double_mat(mat_in, size_mat, size_mat, prec);
 }

 destroy_mat((void**)mat_in, size_mat);
 destroy_mat((void**)mat_out, size_mat);
 destroy_arr((void*)arr);
 destroy_arr((void*)str);

 return 0;
}
