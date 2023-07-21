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

/**
 * @brief Створює массив
 * 
 * Функція  створює массив заданного розміру
 * 
 * @param size розмір массива
 * 
 * @return вказівник на массив
*/
int* create_arr(int size);
/**
 * @brief Знищує массив
 * 
 * Функція бере вказівник на динамічно аллоцирований массив та очищає зайняту пам`ять
 * 
 * @param arr вказівник на массив
*/
void destroy_arr(int* arr);

/**
 * @brief Отримує двовимірну квадратну матрицю, та повертає одновимірний массив який був діагоналлю матриці упорядковуючи її
 * 
 * Функція бере вказівник та створює массив заданного розміру
 * 
 * @param mat_in вхідна матриця
 * @param arr вихідний массив  
 * @param size розмір массива/матриці
*/
int *diagonal(int **mat_in,int *arr,int size);
/**
 * @brief сортування методом бульбашки
 * 
 * @param arr массив який треба сортувати
 * @param size розмір массиву
*/
void bubble_sort(int *arr, int size);
#endif /* LIB_H */
