#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE (1024)
#define ROWS_NUMBER (32)

// => ./main hamlet.txt output.txt
 
int main() { //int main(int argc, char** argv) {

    char inp_name[255] = "";
    printf("Enter the input file name in format .txt: ");
    scanf("%s", inp_name);

    FILE* input;
    FILE* output;
    input = fopen(inp_name, "a+");

    if (input == NULL) {
        perror("Error opening file.");
        return -1;
    }
    // DONE: ret value of fopen

    char** rows, current[STR_SIZE];
    rows = (char**) malloc(sizeof(char*) * ROWS_NUMBER);
    // DONE: what malloc returns ????????? ?? ????? ? ?????? ??? ??????? ??????? size ??? NULL
    
    int count = 0; 
    int reserved = ROWS_NUMBER;
    
    while (fgets(current, STR_SIZE, input)) {

        if (count == reserved) {
            
            rows = realloc(rows, sizeof(char*) * (reserved + ROWS_NUMBER));

            reserved += ROWS_NUMBER;
        }

        rows[count] = malloc(strlen(current) + 1);

        strcpy(rows[count++], current);
    }

    int i = 0; 
    for (i = 0; i < count; i++)
        printf("%s", rows[i]);

    int j = 0; 
    for (i = 0; i < count - 1; i++) {

        for (j = i + 1; j < count; j++) {

            if (strcmp(rows[j], rows[i]) < 0) {

                char* tmp = rows[i];
                rows[i] = rows[j];
                rows[j] = tmp;
            }
        }
        fputs(rows[i], input);
    }

    // qsort
    // ? ???????????? ?? ???, ??? ???? ???????? qsort ? ??????? ???????????, ????? ??? ???????? ?????????.
    // ?????? ? ???? ???????????? 
    
    for (i = 0; i < count; i++)
        printf("%s", rows[i]);
    
    for (i = 0; i < count; i++)
        free(rows[i]);

    free(rows);

    fclose(input);    
    return 0;
}