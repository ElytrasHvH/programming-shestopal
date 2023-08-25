Лабораторна робота №13 Строки (Null-terminated C Strings)

Шестопал Дмитро Олексійович КН 922-Б

Вхідні данні: файл з текстом.

Код:

```c
#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №13. Строки (Null-terminated C Strings)\n\tЗавдання: Знайти всі цифри, які зустрічаються в тексті.\n");
    char* text=NULL;
    size_t num_digits=0;
    printf("Print a text to count all digits in text:\n");
    text=read_all_input();
    if(text==NULL) {
        printf("No text found or an error occured. Aborting.\n");
        return 0;
    }
    for(int i = 0;text[i]!='\0';i++){
        if(isdigit(text[i])){
            num_digits++;
        }
    }
    printf("\nTotal digits found: %lu\n",num_digits);

    free(text);
    return 0;
}
```

1. Ініціалізація змінної для строки тексту та змінної для рахування кількості цифр
2. Запит текста у користувача. Якщо текста не було отримано - закриваємо программу (За допомогою функції read_all_input яка у циклі викликає функцію read_input яка читає по 8192 символів за раз. Зупиняється якщо read_input поверне NULL)
3. Рахуємо кількість цифр у тексті та виводимо.
4. Звільняємо пам'ять та виходимо з программи.

Усі використані функції мають юніт тести задля перевірки їх роботи.

valgrind log:

==643161== Memcheck, a memory error detector
==643161== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==643161== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==643161== Command: cat ./assets/input.txt
==643161== Parent PID: 643160
==643161== 
==643161== 
==643161== HEAP SUMMARY:
==643161==     in use at exit: 0 bytes in 0 blocks
==643161==   total heap usage: 31 allocs, 31 frees, 135,065 bytes allocated
==643161== 
==643161== All heap blocks were freed -- no leaks are possible
==643161== 
==643161== For lists of detected and suppressed errors, rerun with: -s
==643161== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Приклад використання:

1. За допомогою cat:
└─$ cat ./assets/input.txt | ./dist/main.bin

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №13. Строки (Null-terminated C Strings)
        Завдання: Знайти всі цифри, які зустрічаються в тексті.
Print a text to count all digits in text (Press ctrl+D to continue (linux) or ctrl+Z twice (windows)):

Total digits found: 10

2. Прямий ввід

┌──(elytras㉿Elytras)-[~/programming-shestopal/lab13]
└─$ ./dist/main.bin

        Автор: Шестопал Дмитро Олексійович КН922Б.
                Лабораторна №13. Строки (Null-terminated C Strings)
        Завдання: Знайти всі цифри, які зустрічаються в тексті.
Print a text to count all digits in text (Press ctrl+D to continue (linux) or ctrl+Z twice (windows)):
How to use it 101.

Total digits found: 3
