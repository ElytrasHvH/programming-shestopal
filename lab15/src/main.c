#include "lib.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 2
#define OUTPUT_SIZE SIZE*4096

int main(int argc, char* argv[]) {
printf("\n\tАвтор: Шестопал Дмитро Олексійович КН922Б.\n\t\tЛабораторна №15 Структуровані типи даних\n\tЗавдання: \n\n");
    workcollectionmember_s list[SIZE] = {0};
    char* input_file = NULL;
    char* output_file = strdup("./dist/output.txt");
    char* errstr = strdup("OK!");
    char* input_str = NULL;
    char* wcm_string = NULL;
    char output_str[OUTPUT_SIZE]="";
    int errcode = 0;

    size_t input_str_len = 0;
    size_t output_str_len = 0;
    bitmap_t map = (bitmap_t)calloc(SIZE , sizeof(bool));
    searchdata_u data = {.bool_value = true}; 
    field_t field = HAS_PRACTICAL_TASKS;

    handle_args(argc,argv,&input_file,&output_file,&errstr,&errcode);

    read_from_file(input_file, &input_str);
    if (input_str!=NULL) input_str_len = strlen(input_str);
    if (input_str_len!=0) {
        parse_data(input_str,&errstr,&errcode,list,SIZE); 
    }

    if(search_field(list,map,SIZE,field,&data)) {
        for (size_t i = 0; i < SIZE; i++){
            if(map[i]!=0) {
                printf("Found a match in a member №%d\n",i+1);
                destroy_arr(wcm_string);
                wcm_string=work_collection_member_to_string(&list[i]);
                strcat(output_str,wcm_string);
                strcat(output_str,"\n");
            }
        }
        printf("\n");
    } else {
        printf("No match in the given data!\n");
    }
    sort_struct(list,SIZE,field);
    
    for(int i = 0; i<SIZE;i++) {
        printf("LAB #%u is now %d\n",list[i].num,i);
    }
    printf("\n");
    handle_output(output_str,output_file,errstr,errcode);

return 0;
}

