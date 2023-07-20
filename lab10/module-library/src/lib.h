/**
 * @file lib.h
 * @brief Заголовочний файл з прототипами функцій для створення, обчислення та деструкції квадратної матриці та функції НСД.
 */

#ifndef LIB_H
#define LIB_H

/**
 * @brief Створює квадратну матрицю.
 *
 * Функція створює квадратну матрицю заданого розміру та заповнює її елементи.
 *
 * @param size      Розмір матриці.
 * @param randomize Прапорець, який вказує, чи потрібно генерувати випадкові значення (1 - так, 0 - ні).
 * @param limit     Максимальне значення випадкового числа.
 * @param shift     Зсув для випадкового числа.
 * @return          Вказівник на створену матрицю.
 */
int **create_mat(int size, int randomize, int limit, int shift);

/**
 * @brief Звільняє пам'ять, виділену для квадратної матриці.
 *
 * Функція звільняє пам'ять, виділену для квадратної матриці.
 *
 * @param matrix    Вказівник на матрицю.
 * @param size      Розмір матриці.
 */
void destroy_mat(int **matrix, int size);

/**
 * @brief Обчислює квадратну матрицю.
 *
 * Функція обчислює квадратну матрицю шляхом множення матриці на себе.
 *
 * @param mat_in    Вхідна матриця.
 * @param mat_out   Вихідна матриця.
 * @param size      Розмір матриць.
 */
void square_mat(int **mat_in, int **mat_out, int size);

/**
 * @brief Обчислює найбільший спільний дільник (НСД) двох чисел.
 *
 * Функція обчислює найбільший спільний дільник (НСД) двох цілих чисел.
 *
 * @param num1      Перше число.
 * @param num2      Друге число.
 * @return          Найбільший спільний дільник (НСД) чисел num1 та num2.
 */
int gcd(int num1, int num2);

#endif /* LIB_H */