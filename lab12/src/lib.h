/**
 * @file lib.h
 * @brief Заголовочний файл з прототипами функцій для створення, обчислення та деструкції квадратної матриці та функції НСД.
 */
#include <stdbool.h>
#ifndef LIB_H
#define LIB_H

/**
 * @brief Створює массив цілих чисел
 * 
 * Функція створює массив заданного розміру та иніціалізує значення у 0
 * 
 * @param size розмір массива
 * 
 * @return вказівник на массив
*/
int* create_int_arr(int size);

/**
 * @brief Створює массив дійсних чисел 
 * 
 * Функція створює массив заданного розміру та иніціалізує значення у 0
 * 
 * @param size розмір массива
 * 
 * @return вказівник на массив
*/
double *create_double_arr(int size);
/**
 * @brief Знищує массив
 * 
 * Функція бере вказівник на динамічно аллоцирований массив та очищає зайняту пам`ять
 * 
 * @param arr вказівник на массив
*/
void destroy_arr(void* arr);
/**
 * @brief Створює квадратну матрицю цілих чисел.
 *
 * Функція створює квадратну матрицю цілих чисел заданого розміру та заповнює її елементи.
 *
 * @param size Розмір матриці.
 * @param randomize Флаг рандомізації
 * @param limit Ліміт генерації (0 - limit-1)
 * @param shift Зміщення згенерованих чисел (shift - shift+limit-1)
 * @return Вказівник на створену матрицю.
 */
int **create_int_mat(int size, bool randomize, int limit, int shift);

/**
 * @brief Створює квадратну матрицю дійсних чисел.
 *
 * Функція створює квадратну матрицю дійсних чисел заданого розміру та заповнює її елементи.
 *
 * @param size Розмір матриці.
 * @param randomize Флаг рандомізації
 * @param limit Ліміт генерації (0 - limit-1)
 * @param shift Зміщення згенерованих чисел (shift - shift+limit-1)
 * @return Вказівник на створену матрицю.
 */
double **create_double_mat(int size, bool randomize, double limit, double shift);

/**
 * @brief Звільняє пам'ять, виділену для 2d массивів будь-якого типу
 *
 * Функція звільняє пам'ять, виділену для 2d матриці будь-якого типу
 *
 * @param matrix Матриця
 * @param size Розмір матриці.
 */
void destroy_mat(void **matrix, int size);

/**
* @brief Генерує дійсне число у заданному діапазоні
* 
* Функція генерує дійсні числа у заданномоу діапазоні
* 
* @param limit лимит значення (може бути від'ємним та нулем)
* @param shift зміщення (може бути від'ємним та нулем)
* 
* @return згенерованне значення
*/
double generate_random_double_value(double limit, double shift);

/**
* @brief Генерує ціле число у заданному діапазоні
* 
* Функція генерує цілі числа у заданномоу діапазоні
* 
* @param limit лимит значення (може бути від'ємним та нулем)
* @param shift зміщення (може бути від'ємним та нулем)
* 
* @return згенерованне значення
*/
int generate_random_int_value(int limit, int shift);

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
 * @brief Отримує двовимірну квадратну матрицю, та повертає одновимірний массив який був діагоналлю матриці упорядковуючи її
 * 
 * Функція бере вказівник та створює массив заданного розміру
 * 
 * @param mat_in вхідна матриця
 * @param arr вихідний массив  
 * @param size розмір массива/матриці
*/
double *diagonal(double **mat_in,double *arr,int size);
/**
 * @brief сортування методом бульбашки
 * 
 * Функція сортує даний массив за допомогою метода бульбашки
 * 
 * @param arr массив який треба сортувати
 * @param size розмір массиву
*/
void bubble_sort(int *arr, int size);

/**
 * 
 * @brief Принт 2д матриці у консоль
 * 
 * Функція виводить задану матрицю у консоль
 * 
 * @param mat_in Вказівник на матрицю 
 * @param rows Кількість строк
 * @param cols Кількість стовпів
 * 
*/
void print_int_mat(int** mat_in, int rows, int cols);

/**
 * 
 * @brief Принт 2д матриці у консоль
 * 
 * Функція виводить задану матрицю у консоль
 * 
 * @param mat_in Вказівник на матрицю 
 * @param rows Кількість строк
 * @param cols Кількість стовпів
 * 
*/
void print_double_mat(double** mat_in, int rows, int cols);

/**
 * @brief Інверсія матриці методом алгебраічних доповнень
 * 
 * Функція інвертує матрицю. Функція НЕ виділяє пам`ять для матриць. Вона повинна буде виділена заздалегіть. 
 * 
 * @param mat_in Вказівник на матрицю яку треба обернути
 * @param mat_out Вказівник на матрицю де буде зберигатися обернена матриця
 * @param size Розмір матриці
 * 
*/
bool adj_reverse_mat(double **mat_in, double**mat_out, int size);

/**
 * 
 * @brief Пошук детермінанта
 * 
 * Функція шукає детермінант матриці. ФУНКЦІЯ РЕКУРСИВНА!
 * 
 * @param mat Вказівник на матрицю
 * @param size Розмір матриці
 * 
 * @return Детермінант матриці
*/
double get_determinant(double **mat, int size);

/**
 * @brief Обчислює коефіцієнт для елемента матриці.
 *
 * Функція 
 * 
 * @param mat Вихідна матриця.
 * @param temp Матриця для зберігання коефіцієнта.
 * @param p Індекс рядка елемента.
 * @param q Індекс стовпця елемента.
 * @param size Розмір матриці.
 */
void get_cofactor(double **mat, double **temp, int p, int q, int size);
/**
 * @brief Обчислює матрицю алгебраїчних доповнень для квадратної матриці.
 *
 * Функція обчислює алгебраїчні доповненя для кожного елменту матриці і зберігає їх як матрицю
 * 
 * @param mat Вихідна матриця.
 * @param adj Матриця для зберігання результату.
 * @param size Розмір матриці.
 */
void get_adj_matrix(double **mat, double **adj, int size);

/**
 * @brief Міняє місця строк массиву
 *
 * @param Массив у якому треба змінити місяцми
 * @param Перша строка
 * @param Друга строка
 */
void swap_rows(void **mat, int row1, int row2);

#endif /* LIB_H */
