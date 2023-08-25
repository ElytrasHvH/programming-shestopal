Лабораторна робота №14 Взаємодія з файлами

Шестопал Дмитро Олексійович КН 922-Б

Вхідні данні: файл з текстом.

Код:
```c
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
char* errstr = strdup("everything is ok\n");
char* mat_str = NULL;
int errcode = 0;
double* arr=NULL;
double** mat=NULL;
double det=0;
size_t shift = 2;
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

mat=convert_array_to_mat(arr+shift,arr_size-shift,&mat_size);//pointer and size being shifted to exclude size of matrix and it's values from end matrix
det = get_determinant(mat,mat_size);

mat_str = write_double_mat_to_string(mat, mat_size, mat_size, 2);

mat_str_len=strlen(mat_str);
det_len = (size_t)snprintf(NULL, 0, "%.2f\n", det);
prefix_len = strlen("Determinant of the given matrix is: ");
total_len = det_len+prefix_len+mat_str_len+strlen("Input matrix:\n");

output_text=create_string(total_len);
(void)sprintf(output_text,"Input matrix:\n%sDeterminant of the given matrix is: %.2f\n",mat_str,det); 

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
```

1. Ініціалізація усіх необхідніх змінних
2. За допомогою switch по argс обираємо гілку за якою починається виконання программи. Перевіряємо викликав програму саму по собі, програму з шляхом до вхідного файлу або і вхідного файлу і вихідного файлу.
3. Робимо перевірки:
3.1 Чи є у нас права на зчитування
3.2 Чи є у нас права на запис та створювання директорій
Якщо так то читаємо файл.
4. Перевіряємо чи вдалося зчитати хочь щось
5. Парсимо файл та перевіряємо чи вдалося зпарсити файл
6. Перевіряємо що є необхідний мінімум для продовження перевірок (3 числа тобто для матриці 1х1)
7. Перевіряємо що обидва числа що мають бути невід`ємними.
7.1 Перевіряємо що обидва числа є цілими
7.2 Перевіряємо що числа які користувач надав заявляють що матриця квадратна
7.3 Перевіряємо що числа які користувач надав як розмірності матриці є справжніми
7.4 Перевіряємо що матриця не є занадто великою.
8. Конвертуємо одновимірний массив у двовимірний та розраховуємо детермінант
9. Робимо строку яка має в собі матрицю у відформатованому вигляді
9.1 Зчитуємо довжину строки
10. Розраховуємо довжину яку займе детермінант
11. Розраховуємо довжину яку займе префікс
12. Суммуємо щоб отримати повну довжину та створюємо строку потрібної довжини після чого записуємо строку
13. Якщо ніяких помилок не було - Записуємо строку у файл та виводимо у термінал.
13.1 Якщо була помилка щодо файлу вводу/виводу - Виводимо строку з помилкою у термінал.
13.2 Якщо була будь-яка інша помилка - Виводимо строку з помилкою у консоль за записуємо її у файл
14. Звільнюємо пам`ять та закриваємо программу

Усі функції окрім handle_input та handle_output мають юніт тести.
Функції handle_input та handle_output були зроблені лише задля того щоб зменьшити когнітивну важкість програми.

valgrind log:

==672066== Memcheck, a memory error detector
==672066== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==672066== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==672066== Command: ./dist/main.bin ./assets/input.txt ./dist/output.txt
==672066== Parent PID: 672054
==672066== 
==672066== 
==672066== HEAP SUMMARY:
==672066==     in use at exit: 0 bytes in 0 blocks
==672066==   total heap usage: 89 allocs, 89 frees, 35,629 bytes allocated
==672066== 
==672066== All heap blocks were freed -- no leaks are possible
==672066== 
==672066== For lists of detected and suppressed errors, rerun with: -s
==672066== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Приклад використання:

1. Без аргументів:
┌──(elytras㉿Elytras)-[~/programming-shestopal/lab14]
└─$ ./dist/main.bin                  

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №14 Взаємодія з файлами
        Завдання: Визначити детермінант матриці якщо він існує.
No input file provided
Give a file location (1 line, up to 8192 characters):
./assets/input.txt
No output file destination & name provided
Do you want to proceed with the default location? (Y/N)
y
Input matrix:
[        3.00   4.00    5.00    -4.00   ]
[        2.00   5.00    6.00     0.00   ]
[        4.00   5.00    2.00     2.40   ]
[       -5.00   6.00    4.00     3.00   ]

Determinant of the given matrix is: 666.00

(файл збережено у ./dist/output.txt)
2. Лише з вхідним файлом:

┌──(elytras㉿Elytras)-[~/programming-shestopal/lab14]
└─$ ./dist/main.bin ./assets/input.txt                  

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №14 Взаємодія з файлами
        Завдання: Визначити детермінант матриці якщо він існує.
No output file destination & name provided
Do you want to proceed with the default location? (Y/N)
y
Input matrix:
[        3.00   4.00    5.00    -4.00   ]
[        2.00   5.00    6.00     0.00   ]
[        4.00   5.00    2.00     2.40   ]
[       -5.00   6.00    4.00     3.00   ]

Determinant of the given matrix is: 666.00
            
(файл збережено у ./dist/output.txt)                                   
3. З заданим вхідним та вихідніми файлами:

┌──(elytras㉿Elytras)-[~/programming-shestopal/lab14]
└─$ ./dist/main.bin ./assets/input.txt ./dist/output.txt

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №14 Взаємодія з файлами
        Завдання: Визначити детермінант матриці якщо він існує.
Input matrix:
[        3.00   4.00    5.00    -4.00   ]
[        2.00   5.00    6.00     0.00   ]
[        4.00   5.00    2.00     2.40   ]
[       -5.00   6.00    4.00     3.00   ]

Determinant of the given matrix is: 666.00
       
(файл збережено у ./dist/output.txt)                                    
4. Не заданий вихідний файл з не стандартним (за програмою) вихідом

┌──(elytras㉿Elytras)-[~/programming-shestopal/lab14]
└─$ ./dist/main.bin ./assets/input.txt                  

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №14 Взаємодія з файлами
        Завдання: Визначити детермінант матриці якщо він існує.
No output file destination & name provided
Do you want to proceed with the default location? (Y/N)
n
Give output file destination (1 line, up to 8192 characters):
./dist/nondef_output.txt
Input matrix:
[        3.00   4.00    5.00    -4.00   ]
[        2.00   5.00    6.00     0.00   ]
[        4.00   5.00    2.00     2.40   ]
[       -5.00   6.00    4.00     3.00   ]

Determinant of the given matrix is: 666.00
               
(файл збережено у ./dist/output.txt)
