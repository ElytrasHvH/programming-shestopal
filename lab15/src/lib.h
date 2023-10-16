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

//Define bitmap_t
typedef bool* bitmap_t;

// Define the frequency_t enum
typedef enum frequency_t {
    NEVER,
    ONCE_A_WEEK,
    ONCE_A_MODULE,
    ONCE_A_SEMESTER,
    NUM_FREQUENCIES
} frequency_t;

// Define the lab work types
typedef enum labwork_t {
    NO_TYPE,
    WRITE_A_PROGRAM,
    CALCULATE,
    CREATE_A_SCHEME,
    DO_EXPERIMENT,
    NUM_LAB_WORK_TYPES
} labwork_t;

// Define the subject struct
typedef struct subjectinfo_s {
    char prof_surname[256];
    char subject_name[256];
} subjectinfo_s;

// Define the base_work struct
typedef struct basework_s {
    char theme[1024];
    subjectinfo_s subject;
    unsigned int problem_count;
    frequency_t frequency;
    bool has_variation;
} basework_s;

// Define the work_type struct
typedef struct work_s {
    basework_s base;
    bool has_test_questions;
    bool has_practical_tasks;
} work_s;

// Define the lab_work struct
typedef struct labwork_s {
    basework_s base;
    labwork_t type;
    bool is_possible_at_home;
} labwork_s;

//Define member of a struct collection
typedef struct workcollectionmember_s {
    size_t num;
	basework_s base;
	labwork_s lab_work;
	work_s work_type;
} workcollectionmember_s;

//Define enum that corresponds to different fields
typedef enum field_t {
    NONE,
    FREQUENCY,
    LABWORKTYPE,
    PROF_SURNAME,
    SUBJECT_NAME,
    HAS_VARIATION,
    THEME,
    PROBLEM_COUNT,
    HAS_TEST_QUESTIONS,
    HAS_PRACTICAL_TASKS,
    IS_POSSIBLE_AT_HOME
} field_t;

typedef union searchdata_u {
	frequency_t frequency_value;
	labwork_t labwork_type_value;
    unsigned int unsigned_int_value;
    signed int signed_int_value;
    bool bool_value;
    char string[1024];
} searchdata_u;
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
bool split_string_into_words(const char* str, char*** words, size_t* num_words, const char* delimiter);

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

/**
 * @brief Обробити аргументи командної строки задля отримання вхідного на вихідного файлу
 *
 * Функція обробляй аргументи командної строки щоб вилучити шлях до вхідного так вихідного файлу
 * В залежності від кількості аргументів може запитати користувача надати більше аргументів
 *
 * @param argc Кількість аргументів командної строки
 * @param argv Массив строк що має аргументи командної строки
 * @param input_file Вказівник на строки з динамічно виділенної пам`ятью яка зберігає вилучиний шлях до вхідного файлу.
 * @param output_file Вказівник на строки з динамічно виділенної пам`ятью яка зберігає вилучиний шлях до вихідного файлу.
 * @param errstr Вказівник на строки з динамічно виділенної пам`ятью яка зберігає строку з помилкою
 * @param errcode Вказівник на число яке зберігає код помилки. 
 *
 * @note Вказівники для input_file має бути проініціадізованим у NULL. для errstr та output_file це може бути як NULL так і строка проініціалізована динамічна строка за допомогою strdup
 * @note Будь яка помилка в виконанні вимусить функцію поставити errcode на 0
 * 
 * @warning Викликач повинен звільнити пам`ять зайняту input_file, output_file, та errstr.
 */
void handle_args(int argc, char** argv,char** input_file,char** output_file,char** errstr,int* errcode);

/**
 * @brief Функція яка обробляє вихідні данні на основі коду помилки
 * 
 * @param output_text Текст який буде виведен у консоль там у файл.
 * @param output_file Шлях до файлу де буде записані вихідні данні або строка з помилкою (Будь-ласка перевірте заздалегіть що для цього файлу/директорії є права запису, а також що це існуюча директорія)
 * @param errstr Строка з повідомленням помилки
 * @param errcode Код помилки
 *
 * @note Код помилки -1 та 1 зарезервовані коли є проблема з вихідним файлом. у цьому випадку строка з помилкою буде виведена тільки у консоль 
 * @note Будь який інший код помилки окрім 0 запише строку з помилкою у вихідний файл
 * @note Функція не робить ніяких перевірок щодо шляху до файлу та самого файлу виходу
 */
void handle_output(char* output_text,char* output_file,char* errstr,int errcode);

/**
 * @brief Синронизує поля структури-дитини з полями струкури-дорослого в середині workcollectionmember_s.
 *
 * Синронизує поля структури-дитини з полями струкури-дорослого в середині workcollectionmember_s.
 * Копіює значення з base структури у lab_work.base та work_type.base .
 *
 * @param member Вказівник на workcollectionmember_s
 *   - member.base структура є інформациєю яку копіюють для синхронізації.
 *   - member.lab_work.base та member.work_type.base є структурами які синхронизують.
 */
void sync_work_collection_member(workcollectionmember_s* const member);

/**
 * @brief Пошук співпадання поля у коллекції workcollectionmember_s з якоюсь інформацією та збереження на bitmap_t мапі.
 *
 * @param member Вказівник на першого участника коллекції workcollectionmember_s для пошуку.
 * @param map (массив bool) bitmap_t яка використвуюється для зберігання індексів участників коллекціїї у якому знайшли співпадання поля з інформаціюєю яку шукають. 
 * @param size Кількість учстників коллекції та розмір bitmap_t
 * @param field Тип поля для пошуку
 * @param data Вказівник на обїєднання у якому інформація яку шукають.
 * @return Так якщо хоть одне співпадання було, ні інакше.
 * 
 * @note Функція зробленна для того щоб знайти співпадання інформації у участнику коллекції. 
 * @note Розмір bitmap_t має буути таким самим як розмір колекції
 */
bool search_field(const workcollectionmember_s* member, bitmap_t map, const size_t size, const field_t field, const searchdata_u* data);

/**
 * @brief Встановлює код та текст помилки
 *
 * @param errcode Вказівник на змінну errcode яка буде встановлена.
 * @param errstr Строка errstr де буде записана строка помилки.
 * @param code Код помилки.
 * @param errmsg Повідомленння помилки.
 */
void set_error(int* const errcode, char** errstr, const int code, const char* errmsg);

/**
 * @brief Порівняння строк не зважаючи на регістр
 *
 * @param str1 Перша строка
 * @param str2 Друга строка
 * @return Так якщо сроки рівні, інакше ні. 
 */
bool cncasestrcmp(const char* str1, const char* str2);

/**
 * @brief Записує workcollectionmember_s у строку.
 *
 * @param member Вказівник на workcollectionmember_s яку треба записати у строку.
 * 
 * @return Строку з відформатованною workcollectionmember_s.
 */
char* work_collection_member_to_string(const workcollectionmember_s* const member);

/**
 * @brief Парсить (c-csv string) та записує інфорамцію у массив workcollectionmember_s.
 *
 * @param input_str Строка яку треба зпарсити.
 * @param errstr Строка де буде зберігаться повідомлення про помилку.
 * @param errcode Вказівник на змінну де буде зберігатися код помилки.
 * @param struct_ptr Вказівник на початок массиву workcollectionmember_s.
 * @param size Розмір массиву
 */
void parse_data(const char* input_str, char** errstr, int* errcode, workcollectionmember_s* struct_ptr, size_t size);

/**
 * @brief Порівнуює два workcollectionmember_s за полем.
 *
 * @param p_struct1 Вказівник на першу структуру workcollectionmember_s.
 * @param p_struct2 Вказівник на другу струкуру workcollectionmember_s.
 * @param type Поле яке порівнюють.
 * @return Від'ємне якщо p_struct1 < p_struct2, 0 якщо p_struct1 == p_struct2, інакше позитивне.
 * 
 * @note: Частично порівнює строки. використовувати разом з compare_by_field_string
 */
int compare_by_field(const workcollectionmember_s* const p_struct1, const workcollectionmember_s* const p_struct2, field_t type);

/**
 * @brief Міняє местами 2 елементи массиву.
 *
 * @param arr Массив.
 * @param i Індекс першого елементу.
 * @param j Індекс другого елементу.
 * @param size Розмір елементу.
 */
void swap(void* arr, size_t i, size_t j, size_t size);

/**
 * @brief Сортування массиву workcollectionmember_s за полем (числове/булове/строкове).
 *
 * @param member Вказівник на перший елемент массиву workcollectionmember_s.
 * @param member_count Кілкість елементів.
 * @param data Вказівник на об'єднання searchdata_u яке вийде вперед відсортованного массиву.
 * @param type Поле за яким сортуюють.
 */
void sort_struct(workcollectionmember_s* const member, size_t member_count, const searchdata_u* const data, const field_t type);

/**
 * @brief Сортування массиву workcollectionmember_s за полем (не строкою).
 *
 * Функція використовую сортування бульбашкою для сортування массиву workcollectionmember_s за заданним полем.
 * Порівнює значення заданних полей між собою та інформацією яку треба вивести вперед.
 * Якщо значення мають двох участників дорівнюють, вони відсортованні за їх 'num' полем.
 *
 * @param member Вказівник на початок маассиву яке буде відсортоване
 * @param member_count Кількість елементів.
 * @param data Вказівник на обєднанння з якого беруть інформацію участників з якой будуть виводити на початок.
 * @param type Поле за яким сортують.
 */
void sort_struct_no_string(workcollectionmember_s* const member, size_t member_count, const searchdata_u* const data, const field_t type);
/**
 * @brief Порівнює два workcollectionmember_s за полем (строковим).
 *
 * Функція порівнює два workcollectionmember_s за полем (строковим) з data строкою використовуючи як регістро-алежне так и незалежене порівняння.
 *
 * @param member Вказівник на коллекцію workcollectionmember_s.
 * @param mem_num1 Індекс першого участника коллекції.
 * @param mem_num2 Індекс другого участника коллекції.
 * @param data Вказівник на об'єднання з інформаціюєю (строкою).
 * @param type Поле (PROF_SURNAME, SUBJECT_NAME, або THEME) за яким порівнювати.
 * @return 1 якщо перше workcollectionmember_s таке саме як data string а second ні, -1 якщо дурге workcollectionmember_s таке саме як data string а перше ні, 0 якщо вони однакові (однаково дорівнюють або не дорівнюють data string).
 */
int compare_by_field_string(workcollectionmember_s* const member, size_t mem_num1, size_t mem_num2, const searchdata_u* const data, const field_t type);

/** 
 * @brief Сортування коллекції workcollectionmember_s за визначенним полем (та значенням).
 *
 * Сортування коллекції workcollectionmember_s методом бульбашки на основі поля-строки.
 * Виконує порівняння за допомогою compare_by_field щоб визначити чи строки є однаковими (з string.h) а потім виконує регістр-незалежзне порівняння використовуючи cncasestrcmp
 * Якщо вони є однаковими за значенням, вони сортуються за порядковим номером
 *
 * @param member Вказівник на коллекцію workcollectionmember_s яка сортирується.
 * @param member_count Розмір коллекції.
 * @param data Вказівник на об'єднання, яке містить інформацію яка якщо знайдена та буде виведена вперед сортованного массиву.
 * @param type Поле за яким буде відсортован (PROF_SURNAME, SUBJECT_NAME, або THEME).
 */
void sort_struct_string(workcollectionmember_s* const member, size_t member_count, const searchdata_u* const data, const field_t type);

#endif
