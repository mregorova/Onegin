#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define NAME "hamlet.txt"
#define STR_SIZE (1024)
#define ROWS_NUMBER (32)
 
int main() {

    FILE* input;
    char** rows, current[STR_SIZE];
    int i = 0; 
    int j = 0; 
    
    input = fopen(NAME, "r");

    rows = malloc(sizeof(char*) * ROWS_NUMBER);
    
    int reserved = 0;
    reserved = ROWS_NUMBER;
    
    int count = 0; 
    
    while (fgets(current, STR_SIZE, input)) {

        if (count == reserved) {
            
            rows = realloc(rows, sizeof(char*) * (reserved + ROWS_NUMBER));

            reserved += ROWS_NUMBER;
        }

        rows[count] = malloc(strlen(current) + 1);

        strcpy(rows[count++], current);
    }

    for (i = 0; i < count; i++)
        printf("%s", rows[i]);
    
    for (i = 0; i < count - 1; i++) {

        for (j = i + 1; j < count; j++) {

            if (strcmp(rows[j], rows[i]) < 0) {

                char* tmp = rows[i];
                rows[i] = rows[j];
                rows[j] = tmp;
            }
        }
    }
    
    for (i = 0; i < count; i++)
        printf("%s", rows[i]);
    
    for (i = 0; i < count; i++)
        free(rows[i]);

    free(rows);
    
    return 0;
}