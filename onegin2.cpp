// This program was taken from K&R like an example of qsort

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

int createbuf_readlines(FILE *hamlet, char** buf, const char* filename, int num);
void writelines(char **buf, const size_t filesize, const char *filename);
int compare_lines(const void *a, const void *b);
int symbolAmount(char* str, const size_t fileSize, const char symbol);

int main(const char* file1, const char* file2) {
    
    char *buf = NULL;
    int nlines = 0;
    int num = 0;
    int filesize = 0;

    //char* filename = (char*) calloc(FILENAME_MAX, sizeof(char*));//
    char filename[] = "..\\hamlet.txt";                     //it's important to choose appropriate directory
    FILE *hamlet = fopen(filename, "r");
    assert(hamlet != NULL);

    char* str = (char*) calloc(filesize, sizeof(*str));

    if ((nlines = createbuf_readlines(hamlet, &buf, file1, num)) >= 0) {

        size_t nLines = symbolAmount(str, filesize, '\n');
        char** lineptr = (char**) calloc(nLines, sizeof(char*));
        qsort(lineptr, num, sizeof(char), compare_lines);
        writelines(&buf, filesize, file2);
        fclose(hamlet);

        return 0;

    } else {
        printf("error: input is too big to sort\n");
        return 1;
    }

    return 0;
}

int get_filesize(FILE *hamlet) {

    fseek(hamlet, 0, SEEK_END);
    size_t filesize = ftell(hamlet);
    fseek(hamlet, 0, SEEK_SET);

    printf("%d\n", filesize);
    return filesize;
}

int compare_lines(const void *a, const void *b) {

    char arg1 = *(const char*)a;
    char arg2 = *(const char*)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;

    return 0;
}

int symbolAmount(char* str, const size_t filesize, const char symbol) {
    assert(str != nullptr);

    int nSymbols = 0;

    for(size_t i = 0; i < filesize; ++i) {
        if(*str++ == symbol) {
            ++nSymbols;
        }
    }

    return nSymbols;
}

//read lines:
int createbuf_readlines(FILE *hamlet, char** buf, const char* filename, int num) { // rename

    //assert(line != NULL);

    struct stat buff;

    fstat(fileno(hamlet), &buff);
    *buf = (char*)calloc((buff.st_size + 1), sizeof(char));
    assert (buf != NULL);

    num = fread(*buf, sizeof(char), buff.st_size, hamlet);

    return num;
}

//write lines:
void writelines(char **buf, const size_t filesize, const char *filename) {

    FILE *hamlet = fopen(filename, "w");
    assert(hamlet != NULL);

    fwrite(*buf, sizeof(char), filesize, hamlet);

    //for (i = 0; i < nlines; i++)
    //    printf("%s\n", lineptr[i]);
}

void free(char* lineptr, char* buf) { // rename 
    free(lineptr);
    free(buf);
}

//write qsort                                                  DONE
//swap calloc with alloc                                       DONE
//change getline                                               DONE
//split to separate funcs
//change .c to .cpp                                            DONE
//think about asserts                                          DONE?