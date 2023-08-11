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
    printf("Text:\n%s",text);
    for(int i = 0;text[i]!='\0';i++){
        if(isdigit(text[i])){
            num_digits++;
        }
    }
    printf("\nTotal digits found: %lu\n",num_digits);
    free(text);
    return 0;
}
