#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №12.\n\tЗавдання: Визначити зворотню матрицю\n");
    srand((unsigned int)time(NULL));

    double **mat_in = NULL;
    double **mat_out = NULL;
    int size = 0;
    bool exist = false;
    int precision = 2;

    size_t count = 0;
    printf("Waiting for user input. Press ctrl+d (Linux) or ctrl+z (Windows) to finish entering data.\n");

    double *arr = NULL;
    while (arr == NULL) {
        arr = read_input(stdin, &count);
        if (arr == NULL && feof(stdin)) {
            printf("No input given. Exiting(arr).\n");
            return 0;
        }
    }

    if (count == 0) {
        printf("No input entered. Exiting(count).\n");
        destroy_arr(arr);
        return 0;
    }

    if (size == (int)round(sqrt((double)count)) * (int)round(sqrt((double)count))) {
        mat_in = convert_array_to_mat(arr, count, &size);
        mat_out = create_double_mat(size, 0, 0, 0);
        exist = adj_reverse_mat(mat_in, mat_out, size);
        printf("Your matrix:\n");
        print_double_mat(mat_in, size, size, precision);

        if (exist) {
            printf("Inverse matrix:\n");
            print_double_mat(mat_out, size, size, precision);
            destroy_mat((void **)mat_in, size);
            destroy_mat((void **)mat_out, size);
        } else {
            printf("Inverse matrix doesn't exist for this one\n");
        }
    } else {
        printf("Amount of numbers wasn't a perfect square\nHere is the closest one to yours\n");
        mat_in = convert_array_to_mat(arr, count, &size);
        print_double_mat(mat_in, size, size, precision);
        destroy_mat((void **)mat_in, size);
    }

    destroy_arr(arr);

    return 0;
}
