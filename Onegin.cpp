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

void set (char **buf, const char* arr, const int textlen, const int len) {     //доделать переименовки (buf or str)
    char** charptr = buf;
    arr[0].str = buf;
    
    while (charptr - text < textlen) {
        if (*charptr == '\0' || *charptr == '\n') {
            arr[0].len = charptr - arr[0].str;
            charptr++;
            break;
        }
        charptr++;
    }

    for (int i = 1; i < len; i++) {
        arr[i].str = charptr;
    
        while (charptr - text < textlen) {
            if (*charptr == '\0' || *charptr == '\n') {
                arr[i].len = charptr - arr[i].str;
                charptr++;
                break;
            }
            charptr++;
        }
    }
}

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
        char** lineptr = (char**)calloc(nLines, sizeof(char*));
        
        split_str(**buf, len, nlines);

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

bool isUsless (char ch) {                                          //make all \ symbols equivalent
    const char less[] = " \0\n\t\r*.";
    for (int i = 0; less[i] != '\0'; i++) {
        if (less[i] == ch) {
            return true;
        }
    }
    return false;
}

int split_str (char **buf, int* const len) {                //this function splits string to array of ptrs
    assert(text != NULL && "pointers mustn't be NULL");

    int pointer = 0;
    int cnt   = 0;

    bool isonLine = false;

    for (int i = 0; i < *len; i++) {
        if (isonLine) {
            if (buf[i] == '\0' || buf[i] == '\n') {
                cnt++;
                isonLine = false;  
            }
            buf[i - pointer] = buf[i];
        } else {
            if (isUsless(buf[i])) {
                pointer++;
            } else {
                buf[i - pointer] = buf[i];
                isonLine = true;
            }
        }
    }

    for (int i = *len - pointer; i < *len; i++) {
        buf[i] = '\0';
    }

    *len -= pointer;

    return cnt;
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
                                   DONE?