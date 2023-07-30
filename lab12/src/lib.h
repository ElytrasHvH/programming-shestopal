#ifndef LIB_H
#define LIB_H

/**
 * @file lib.h
 * @brief Заголовочний файл з декларацією та описом функцій і структур бібліотеки
 */

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Створює двовимірний масив цілих чисел.
 *
 * @param size      Розмір квадратного масиву.
 * @param randomize Якщо true, елементи масиву ініціалізуються випадковими значеннями.
 * @param limit     Верхній ліміт для випадкових значень елементів.
 * @param shift     Зсув для випадкових значень елементів.
 * @return          Вказівник на створений масив цілих чисел.
 */
int **create_int_mat(size_t size, bool randomize, int limit, int shift);

/**
 * Створює двовимірний масив дійсних чисел.
 *
 * @param size      Розмір квадратного масиву.
 * @param randomize Якщо true, елементи масиву ініціалізуються випадковими значеннями.
 * @param limit     Верхній ліміт для випадкових значень елементів.
 * @param shift     Зсув для випадкових значень елементів.
 * @return          Вказівник на створений масив дійсних чисел.
 */
double **create_double_mat(size_t size, bool randomize, double limit, double shift);

/**
 * Створює масив цілих чисел.
 *
 * @param size Розмір масиву.
 * @return    Вказівник на створений масив цілих чисел.
 */
int *create_int_arr(size_t size);

/**
 * Створює масив дійсних чисел.
 *
 * @param size Розмір масиву.
 * @return    Вказівник на створений масив дійсних чисел.
 */
double *create_double_arr(size_t size);

/**
 * Звільняє пам'ять, видалення масиву або матриці.
 *
 * @param arr Вказівник на масив або матрицю.
 */
void destroy_arr(void *arr);

/**
 * Звільняє пам'ять, видаляє двовимірний масив.
 *
 * @param matrix Вказівник на двовимірний масив.
 * @param size   Розмір масиву (кількість рядків).
 */
void destroy_mat(void **matrix, size_t size);

/**
 * Генерує випадкове дійсне число в заданому діапазоні.
 *
 * @param limit Верхній ліміт діапазону.
 * @param shift Зсув діапазону.
 * @return      Випадкове дійсне число.
 */
double generate_random_double_value(double limit, double shift);

/**
 * Генерує випадкове ціле число в заданому діапазоні.
 *
 * @param limit Верхній ліміт діапазону.
 * @param shift Зсув діапазону.
 * @return      Випадкове ціле число.
 */
int generate_random_int_value(int limit, int shift);

/**
 * Обчислює квадрат матриці цілих чисел.
 *
 * @param mat_in  Вхідна матриця.
 * @param mat_out Матриця для результату (квадрат вхідної матриці).
 * @param size    Розмір квадратної матриці.
 */
void square_mat(int **mat_in, int **mat_out, int size);

/**
 * Обчислює найбільший спільний дільник двох цілих чисел.
 *
 * @param num1 Перше ціле число.
 * @param num2 Друге ціле число.
 * @return     Найбільший спільний дільник двох чисел.
 */
int gcd(int num1, int num2);

/**
 * Заповнює масив діагоналлю квадратної матриці.
 *
 * @param mat_in Вхідна матриця.
 * @param arr    Масив, який буде заповнений діагоналлю матриці.
 * @param size   Розмір квадратної матриці.
 * @return       Вказівник на масив з діагоналлю.
 */
double *diagonal(double **mat_in, double *arr, int size);

/**
 * Сортує масив цілих чисел методом бульбашки.
 *
 * @param arr  Масив для сортування.
 * @param size Розмір масиву.
 */
void bubble_sort(int *arr, int size);

/**
 * Виводить на екран цілочисельну матрицю.
 *
 * @param mat_in Матриця, яку треба вивести.
 * @param rows   Кількість рядків у матриці.
 * @param cols   Кількість стовпців у матриці.
 */
void print_int_mat(int **mat_in, size_t rows, size_t cols);

/**
 * Виводить на екран дійсну матрицю з заданою точністю.
 *
 * @param mat_in Матриця, яку треба вивести.
 * @param rows   Кількість рядків у матриці.
 * @param cols   Кількість стовпців у матриці.
 * @param prec   Точність чисел після десяткової коми.
 */
void print_double_mat(double **mat_in, size_t rows, size_t cols, int prec);

/**
 * Обчислює обернену матрицю для дійсної матриці.
 *
 * @param mat_in  Вхідна матриця.
 * @param mat_out Вихідна матриця (обернена матриця).
 * @param size    Розмір квадратної матриці.
 * @return        True, якщо матрицю вдалося обчислити, інакше False.
 */
bool adj_reverse_mat(double **mat_in, double **mat_out, size_t size);

/**
 * Обчислює визначник квадратної матриці.
 *
 * @param mat  Матриця, визначник якої потрібно знайти.
 * @param size Розмір квадратної матриці.
 * @return     Значення визначника матриці.
 */
double get_determinant(double **mat, size_t size);

/**
 * Обчислює доповнення до заданого елементу матриці.
 *
 * @param mat   Вхідна матриця.
 * @param temp  Допоміжна матриця для обчислення доповнення.
 * @param p     Рядок елемента, для якого знаходимо доповнення.
 * @param q     Стовпець елемента, для якого знаходимо доповнення.
 * @param size  Розмір квадратної матриці.
 */
void get_cofactor(double **mat, double **temp, size_t p_index, size_t q_index, size_t size);

/**
 * Обчислює матрицю ад'юнкту для заданої матриці.
 *
 * @param mat   Вхідна матриця.
 * @param adj   Матриця, куди буде записана ад'юнкта.
 * @param size  Розмір квадратної матриці.
 */
void get_adj_matrix(double **mat, double **adj, size_t size);

/**
 * Міняє місцями два рядки в двовимірному масиві.
 *
 * @param mat   Вхідний двовимірний масив.
 * @param row1  Індекс першого рядка.
 * @param row2  Індекс другого рядка.
 */
void swap_rows(void **mat, size_t row1, size_t row2);

/**
 * Пропускає пробіли та символи табуляції в рядку.
 *
 * @param str Вказівник на рядок, який буде пересунуто на перший символ після пробілів.
 */
const char* skip_whitespace(const char *str);

bool parse_sign(const char** str, bool* negative);

bool parse_numeric_part(const char** str, double* num, int* decimal_count);

bool parse_exponent(const char** str, int* exp_val, bool* exp_negative);
/**
 * Парсить дійсне число з рядка з додатковими опціями.
 *
 * @param str     Вказівник на рядок, який буде проаналізовано.
 * @param result  Вказівник, в який буде записане знайдене дійсне число.
 * @return        True, якщо парсинг вдалий, інакше False.
 */
bool custom_parse_double(const char *str, double *result);

/**
 * Зчитує вхідні дані з файлового потоку і повертає масив чисел.
 *
 * @param stream Вказівник на файловий поток.
 * @param count  Вказівник, який зберігає кількість зчитаних чисел.
 * @return       Вказівник на масив з числами.
 */
double *read_input(FILE *stream,size_t *count);

/**
 * Запитує користувача про введення даних з файлового потоку.
 *
 * @param stream Вказівник на файловий поток.
 * @return       True, якщо користувач ввів дані, інакше False.
 */
bool prompt_for_input(FILE *stream);

/**
 * Конвертує одновимірний масив дійсних чисел в двовимірний за заданим розміром.
 *
 * @param arr      Одновимірний масив з дійсними числами.
 * @param count    Кількість елементів у масиві.
 * @param size     Вказівник на змінну, в яку буде записано розмір матриці.
 * @return         Вказівник на двовимірний масив (матрицю).
 */
double **convert_array_to_mat(const double *arr, size_t count, size_t *size);


/**
 * Зчитує та парсить рядок з введеними користувачем даними про числа з плаваючою точкою.
 *
 * @param input_line Рядок з введеними даними.
 * @param arr        Вказівник на масив дійсних чисел.
 * @param size       Кількість елементів у масиві arr.
 * @param capacity   Загальна ємність масиву arr (кількість виділеної пам'яті).
 * @return           True, якщо парсинг вдалося, інакше False.
 */
bool read_and_parse_line(const char *input_line, double **arr, size_t *size, size_t *capacity);


void add_double_to_array(double **arr, size_t *size, size_t *capacity, double num);

#endif
