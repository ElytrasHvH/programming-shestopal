#include "lib.h"
#include <stdio.h>

int main()
{
    // Set the size of the matrix
    int size = 3;

    // Create a matrix with random values
    int **matrix = create_mat(size, 1, 10, 0);
    int **squared_matrix = create_mat(size, 0, 0, 0);

    // Print the original matrix
    printf("Original matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Compute the square of the matrix
    square_mat(matrix, squared_matrix, size);

    // Print the squared matrix
    printf("\nSquared matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", squared_matrix[i][j]);
        }
        printf("\n");
    }

    // Compute the GCD of two numbers
    int num1 = 12;
    int num2 = 18;
    int result = gcd(num1, num2);
    printf("\nThe GCD of %d and %d is %d\n", num1, num2, result);

    // Destroy the matrices
    destroy_mat(matrix, size);
    destroy_mat(squared_matrix, size);

    return 0;
}
