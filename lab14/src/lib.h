#ifndef LIB_H
#define LIB_H
/**
 * @file lib.h
 * @brief Заголовочний файл з декларацією та описом функцій і структур бібліотеки
 */

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 * Створює двовимірний масив цілих чисел.
 *
 * @param size Розмір матриці (кількість рядків та стовпців).
 * @param randomize Прапорець, який вказує, чи заповнювати матрицю випадковими значеннями.
 * @param limit Максимальне значення випадкових чисел.
 * @param shift Зсув для випадкових чисел.
 * @return Вказівник на створений масив.
 */
int **create_int_mat(size_t size, bool randomize, int limit, int shift);

/**
 * Створює двовимірний масив дійсних чисел.
 *
 * @param size Розмір матриці (кількість рядків та стовпців).
 * @param randomize Прапорець, який вказує, чи заповнювати матрицю випадковими значеннями.
 * @param limit Максимальне значення випадкових чисел.
 * @param shift Зсув для випадкових чисел.
 * @return Вказівник на створений масив.
 */
double **create_double_mat(size_t size, bool randomize, double limit, double shift);

/**
 * Створює одновимірний масив цілих чисел.
 *
 * @param size Розмір масиву.
 * @return Вказівник на створений масив.
 */
int *create_int_arr(size_t size);

/**
 * Створює одновимірний масив дійсних чисел.
 *
 * @param size Розмір масиву.
 * @return Вказівник на створений масив.
 */
double *create_double_arr(size_t size);

/**
 * Створює одновимірний масив символів.
 *
 * @param size Розмір масиву.
 * @return Вказівник на створений масив.
 */
char *create_char_arr(size_t size);

/**
 * Створює рядок заданого розміру.
 *
 * @param size Розмір рядка (кількість символів).
 * @return Вказівник на створений рядок.
 */
char *create_string(size_t size);

/**
 * Звільняє пам'ять, зарезервовану під масив.
 *
 * @param arr Вказівник на масив для звільнення пам'яті.
 */
void destroy_arr(void *arr);

/**
 * Звільняє пам'ять, зарезервовану під двовимірний масив.
 *
 * @param matrix Вказівник на двовимірний масив для звільнення пам'яті.
 * @param size Розмір матриці (кількість рядків та стовпців).
 */
void destroy_mat(void **matrix, size_t size);

/**
 * Збільшує ємність масиву дійсних чисел.
 *
 * @param arr Вказівник на масив для збільшення ємності.
 * @param capacity Вказівник на змінну, що містить поточну ємність масиву.
 */
void increase_capacity(double **arr, size_t *capacity);

/**
 * Генерує випадкове ціле число в заданому діапазоні.
 *
 * @param limit Максимальне значення випадкового числа.
 * @param shift Зсув для випадкового числа.
 * @return Випадкове ціле число.
 */
int generate_random_int_value(int limit, int shift);

/**
 * Генерує випадкове дійсне число в заданому діапазоні.
 *
 * @param limit Максимальне значення випадкового числа.
 * @param shift Зсув для випадкового числа.
 * @return Випадкове дійсне число.
 */
double generate_random_double_value(double limit, double shift);

/**
 * Сортує масив цілих чисел методом бульбашкового сортування.
 *
 * @param arr Вказівник на масив для сортування.
 * @param size Розмір масиву.
 */
void bubble_sort(int *arr, int size);

/**
 * Обчислює квадрат матриці.
 *
 * @param mat_in Вказівник на вхідну матрицю.
 * @param mat_out Вказівник на матрицю-результат (квадрат вхідної матриці).
 * @param size Розмір матриці (кількість рядків та стовпців).
 */
void square_mat(int **mat_in, int **mat_out, int size);

/**
 * Виділяє діагональ елементів вхідної матриці у вихідний масив.
 *
 * @param mat_in Вказівник на вхідну матрицю.
 * @param arr Вказівник на масив, у який буде збережено діагональ.
 * @param size Розмір матриці (кількість рядків та стовпців).
 * @return Вказівник на масив, у якому збережено діагональ.
 */
double *diagonal(double **mat_in, double *arr, int size);


/**
 * Функція для обернення матриці за допомогою LU-розкладу з частковим вибором головного елемента.
 *
 * @param mat_in Вказівник на вхідну квадратну матрицю (2D масив double).
 * @param mat_out Вказівник на вихідну матрицю, в якій зберігатиметься обернена матриця (2D масив double).
 * @param size Розмір квадратної матриці (кількість рядків/стовпців).
 * @return Логічне значення, яке вказує, чи було успішне обертання матриці (true), або чи матриця є невиродженою (false).
 *
 * @note Функція використовує LU-розклад для обчислення оберненої матриці з вхідної матриці `mat_in`.
 *       Обернена матриця зберігається у вихідній матриці `mat_out`.
 *       Функція повертає true, якщо обертання вдалося, і false, якщо матриця є невиродженою (неможливо обернути).
 */
bool inverse_mat(double** mat_in, double** mat_out, size_t size);

/**
 * Функція для виконання LU-розкладу з частковим вибором головного елемента.
 * 
 * @param mat Вхідна матриця `mat`.
 * @param size Розмір матриці (кількість рядків/стовпців).
 * @param LU Вихідна матриця `LU`, яка міститиме результати LU-розкладу.
 * @param pivot Вихідний масив `pivot`, в якому будуть збережені індекси перестановок рядків.
 * 
 * @note Функція виконує LU-розклад вхідної матриці `mat` з частковим вибором головного елемента.
 *       Результати зберігаються у вихідній матриці `LU` та масиві `pivot`.
 */
void lu_decomposition(double** mat, size_t size, double** lu_matrix,int* pivot);

/**
 * Функція для розв'язання лінійної системи рівнянь за допомогою LU-розкладу.
 *
 * @param lu_mat Вказівник на LU-розклад матриці коефіцієнтів (2D масив double).
 * @param size Розмір матриці та векторів (кількість рядків/стовпців).
 * @param vec_b Вказівник на вектор правої частини системи (1D масив double).
 * @param vec_x Вказівник на вектор-розв'язок системи (1D масив double).
 *
 * @note Функція безпосередньо змінює вектор `vec_x`, щоб зберігати розв'язок.
 */
void lu_solve(double** lu_mat, size_t size,const double* vec_b, double* vec_x);
/**
 * Функція для обчислення визначника з LU-розкладу.
 * 
 * @param LU Вхідна матриця `LU`, яка містить результати LU-розкладу.
 * @param size Розмір матриці (кількість рядків/стовпців).
 * @param pivot Вхідний масив `pivot` з індексами перестановок рядків.
 * 
 * @return Обчислений визначник матриці, заснований на LU-розкладі.
 * 
 * @note Функція обчислює визначник матриці, використовуючи результати LU-розкладу.
 *       Також, вона коригує знак визначника на підставі кількості перестановок рядків,
 *       які відбулися під час LU-розкладу.
 */
double determinant_from_lu(double** lu_matrix, size_t size,const int* pivot);

/**
 * Функція для отримання визначника матриці.
 * 
 * @param mat Вхідна матриця `mat`.
 * @param size Розмір матриці (кількість рядків/стовпців).
 * 
 * @return Обчислений визначник матриці.
 * 
 * @note Це головна функція для отримання визначника вхідної матриці `mat`.
 *       Функція використовує LU-розклад з частковим вибором головного елемента для обчислення визначника,
 *       не змінюючи оригінальну матрицю. Функція спочатку створює тимчасову копію `mat` у вигляді матриці `mat_clone`.
 *       Далі створюються матриця LU та масив `pivot` для LU-розкладу.
 *       Виконується LU-розклад, після чого обчислюється визначник з результатів LU-розкладу та звільняються тимчасові матриці.
 */
double get_determinant(double** mat, size_t size);

/**
 * Отримує коефіцієнт матриці, який відповідає за доповнення до мінора.
 *
 * @param mat Вказівник на матрицю.
 * @param temp Вказівник на тимчасову матрицю.
 * @param p_index Індекс рядка, який виключається з розрахунку мінора.
 * @param q_index Індекс стовпця, який виключається з розрахунку мінора.
 * @param size Розмір матриці (кількість рядків та стовпців).
 */
void get_cofactor(double **mat, double **temp, size_t p_index, size_t q_index, size_t size);

/**
 * Отримує матрицю спряженої матриці.
 *
 * @param mat Вказівник на вхідну матрицю.
 * @param adj Вказівник на матрицю, де буде збережена спряжена матриця.
 * @param size Розмір матриць (кількість рядків та стовпців).
 */
void get_adj_matrix(double **mat, double **adj, size_t size);

/**
 * Обмінює місцями два рядки в матриці.
 *
 * @param mat Вказівник на матрицю.
 * @param row1 Індекс першого рядка.
 * @param row2 Індекс другого рядка.
 */
void swap_rows(void **mat, size_t row1, size_t row2);

/**
 * Перетворює одновимірний масив у двовимірний.
 *
 * @param arr Вказівник на одновимірний масив.
 * @param count Кількість елементів у масиві.
 * @param size Вказівник на змінну, у якій буде збережено розмір матриці (кількість рядків та стовпців).
 * @return Вказівник на створений двовимірний масив.
 */
double** convert_array_to_mat(const double *arr, size_t count, size_t *size);

/**
 * Пропускає пробіли на початку рядка.
 *
 * @param str Вказівник на рядок.
 * @return Вказівник на перший не пробільний символ у рядку.
 */
const char* skip_whitespace(const char *str);

/**
 * Очищує вхідний потік вводу.
 *
 * @param stream Вказівник на потік вводу.
 */
void clear_input_line(FILE *stream);

/**
 * Зчитує ввід користувача з консолі який не більше ніж 8192 символів.
 *
 * @return Вказівник на рядок, який містить ввід користувача або NULL якщо нічого не було.
 */
char* read_input();

/**
 * Зчитує ввід однієї строки користувача з консолі.
 *
 * @return Вказівник на рядок, який містить ввід користувача або NULL якщо нічого не було.
 */
char* read_input_line();

/**
 * Зчитує ввід користувача з консолі.
 *
 * @return Вказівник на рядок, який містить ввід користувача або NULL якщо нічого не було.
 */
char* read_all_input();
/**
 * Запитує користувача про ввід даних.
 *
 * @return true, якщо був успішний ввід, або false, якщо ввід був не успішним.
 */
bool prompt_for_input();

/**
 * Розділяє рядок на слова.
 *
 * @param str Вказівник на рядок для розділення.
 * @param words Вказівник на масив вказівників, де будуть збережені слова.
 * @param numWords Вказівник на змінну, де буде збережена кількість слів.
 * @return true, якщо розділення вдалося, або false, якщо не вдалося.
 */
bool split_string_into_words(const char *str, char ***words, size_t *numWords);

/**
 * Розбирає рядок і витягає з нього дійсні числа, зберігаючи їх у масиві arr.
 *
 * @param str Рядок для розбору.
 * @param arr Вказівник на масив дійсних чисел, де зберігатимуться результати розбору.
 * @param size Вказівник на змінну, де буде збережено кількість витягнутих дійсних чисел.
 * @return true, якщо розбір вдався і були витягнуті дійсні числа, або false, якщо виникла помилка.
 */
bool parse_string(const char *str, double **arr, size_t *size);

/**
 * Перетворює слово на дійсне число. Сприймає усю строку як одне слово, тому якщо треба із строки отримати більше однієй цифри треба використати parse_string або split_string_into_words разом з word_to_double
 * @param str Рядок, що містить слово для перетворення.
 * @return Значення дійсного числа, отримане зі слова, або 0.0, якщо перетворення не вдалося.
 */
double word_to_double(const char *str);

/**
 * Перевіряє, чи містить рядок певний символ.
 *
 * @param str Вказівник на рядок для перевірки.
 * @param c Символ, який перевіряється.
 * @return true, якщо символ міститься у рядку, або false, якщо ні.
 */
bool contains_char(const char *str, char c);

/**
 * Видаляє всі входження певного символа з рядка.
 *
 * @param str Вказівник на рядок, з якого будуть видалені символи.
 * @param chr Символ, який буде видалено.
 */
void remove_char(char *str, char chr);

/**
 * Збільшує розмір рядка, на заданний розмір.
 *
 * @param str Вказівник на рядок, який потрібно збільшити.
 * @param size Розмір на який треба збільшити
 * @return Вказівник на новий рядок, який має подвоєний розмір початкового рядка.
 */
char* increase_string_size(char *str,size_t size);

/**
 * Переводить усі букви у строці у нижній регістр,якщо вони є
 * 
 * @param str строка у якій букви будуть змінюватися на нижній регістр
*/
void convert_to_lowercase(char* str);
/**
 * Шукає символ у строці и відрізає усе інше що э зліва від нього. Якщо такого символу не було строка залишається незмінною
 *
 * @param str Вказівник на рядок для відрізання
 * @param chr символ який шукає
 */
void cut_string_left(char **str,char chr);

/**
 * Шукає символ у строці и відрізає усе інше що э справа від нього. Якщо такого символу не було строка залишається незмінною
 *
 * @param str Вказівник на рядок для відрізання
 * @param chr символ який шукає
 */
void cut_string_right(char** str, char chr);
/**
 * Стискає рядок, видаляючи всі пробіли і переноси рядка.
 *
 * @param str Вказівник на рядок, який потрібно стиснути.
 */
void compress_string(char *str);

/**
 * Видаляє всі входження символу, крім першого, з рядка.
 *
 * @param str Вказівник на рядок, з якого будуть видалені всі символи, крім першого входження.
 * @param chr Символ, який не видаляється і залишається у рядку.
 */
void remove_all_chars_except_first(char *str, char chr);

/**
 * Фільтрує строку видаляючи з неї непотрібні символи.
 * 
 * @param unfiltered_str строка яку треба відфільтрувати
 * @param allowed_chars массив символів які потрібно залишити
 * @return
*/
char* filter_string(const char* unfiltered_str, const char* allowed_chars);

/**
 * Фильітрує строку видаляючи з неї символи які не є частинами числа та приводить до потрібного вигляду
 * 
 * @param unfiltered_str Строка яку треба відфільтрувати. Уся строка сприймається як одне слово
 * @return Новий массив з відфільтрованною строкою або NULL якщо строка пуста
*/
char* filter_number_string(const char* unfiltered_str);
/**
 * Перевіряє, чи є рядок від'ємним числом.
 *
 * @param str Вказівник на рядок для перевірки.
 * @return true, якщо рядок представляє від'ємне число, або false, якщо ні.
 */
bool is_negative(const char *str);

/**
 * Додає дійсне число до масиву дійсних чисел arr.
 *
 * @param arr Вказівник на вказівник на масив дійсних чисел.
 * @param size Вказівник на змінну, що зберігає поточний розмір масиву arr.
 * @param capacity Вказівник на змінну, що зберігає поточну ємність масиву arr.
 * @param num Дійсне число, яке буде додане до масиву.
 */
void add_double_to_array(double **arr, size_t *size, size_t *capacity, double num);

/**
 * Виводить на екран матрицю цілих чисел.
 *
 * @param mat_in Вказівник на вказівник на матрицю цілих чисел.
 * @param rows Кількість рядків у матриці.
 * @param cols Кількість стовпців у матриці.
 */
void print_int_mat(const int **mat_in, const size_t rows, const size_t cols);

/**
 * Виводить на екран матрицю дійсних чисел з заданою точністю.
 *
 * @param mat_in Вказівник на вказівник на матрицю дійсних чисел.
 * @param rows Кількість рядків у матриці.
 * @param cols Кількість стовпців у матриці.
 * @param prec Кількість знаків після десяткової коми для виведення дійсних чисел.
 */
void print_double_mat(double** mat_in, const size_t rows, const size_t cols, const int prec);

/**
 * Знаходить найбільший спільний дільник двох цілих чисел.
 *
 * @param num1 Перше ціле число.
 * @param num2 Друге ціле число.
 * @return Найбільший спільний дільник num1 та num2.
 */
int gcd(int num1, int num2);

/**
 * Перевіряє, чи є число ідеальним квадратом.
 *
 * @param num Число для перевірки.
 * @return true, якщо число є ідеальним квадратом, або false, якщо ні.
 */
bool is_perfect_square(int num);

/**
 * @brief Знаходить найменьше ціле число, квадрат якого дорівнює заданному числу або найближчему більшему числу.
 * Якщо вхідне число від'ємне, функція повертає -1, оскільки квадрат від`ємних чисел не визначений.
 * 
 * @param num Вхідне число, для якого знаходиться ціле число, квадрат якого менше або дорівнює йому.
 * @return Ціле число, яке є квадратом заданного числа або найближчего до нього.
 */
int get_int_square_root(int num);

/**
 * Функція що перевіряє наявність вхідного файлу. Наявність вихідної директорії
*/
int check_files(char* input_file, char* output_file);

/**
 * Функція що зчитує данні зі строки та зберігає у строці
 * 
 * @note result_string має бути NULL, функція виділить пам`ять для строки. Якщо під час зчитування буде помилка - result_string залишиться NULL. немає бути витоку пам`яті
 * 
 * @param input_file шлях до вхідного файлу
 * @param result_string строка з данними
*/
void read_from_file(char* input_file,char** result_string);

/**
 * Функція що записує данні у файл
 * @param output_file - файл у який треба писати данні (разом зі шляхом) 
 * @param data - данні які треба буде писати
*/
void write_to_file(char* output_file,char* data);

/**
 * Функція що перевіряє наявність директорії
 *
 * @param path шлях до директорії
 * @return 0 якщо не існує 1 якщо існує -1 якщо NULL строка
*/
int directory_exists(const char *path);

/**
 * Функція яка записує відформатовану матрицю у строку
 * 
 * @param mat_in матриця яку будуть записувати
 * @param rows кількість строк
 * @param cols кількість стовпців
 * @param prec кількість знаків після коми
 * 
 * @return Строка яка має массив у відформатованному вигляді.
*/
char*write_double_mat_to_string(double **mat_in, const size_t rows, const size_t cols, const int prec);
#endif
