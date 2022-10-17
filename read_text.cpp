#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

void set (const String text, poemString* const arr, const int textlen, const int len);
int input(String* text, int* textlen, const char* file1, const char* file2);
int create_buf_read_lines(FILE *hamlet, const String text, const char* filename, int num);
int symbol_amount(char* str, const size_t fileSize, const char symbol);
int split_str (const String text, int* const len);

void set (const String text, poemString* const arr, const int textlen, const int len) {
    String charptr = text;
    arr[0].str = text;
    
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

int input(char **text, int* textlen) {
    
    **text = NULL;
    int nlines = 0;
    int num = 0;
    int filesize = 0;

    //char* filename = (char*) calloc(FILENAME_MAX, sizeof(char*));//
    char filename[] = "..\\hamlet.txt";                 //it's important to choose appropriate directory
    FILE *hamlet = fopen(filename, "r");
    assert(hamlet != NULL);

    struct stat buff;
    fstat(fileno(hamlet), &buff);

    *text = (char*)calloc((buff.st_size + 1), sizeof(char));
    assert (text != NULL);

    nlines = fread(*text, sizeof(char), *textlen, hamlet);

    char* str = (char*) calloc(filesize, sizeof(*str));

    if (nlines >= 0) return 1;                                 //process error

    size_t nLines = symbol_amount(str, filesize, '\n');
    char** lineptr = (char**)calloc(nLines, sizeof(char*));
    
    split_str(*text, textlen);

    //qsort(lineptr, num, sizeof(char), compare_lines);
    //write_lines(*text, filesize, file2);
    fclose(hamlet);

    return 0;
}

int split_str (String const text, int* const len) {                //this function splits string to array of ptrs
    assert(text != NULL && "pointers mustn't be NULL");

    int pointer = 0;
    int cnt   = 0;

    bool isonLine = false;

    for (int i = 0; i < *len; i++) {
        if (isonLine) {
            if (text[i] == '\0' || text[i] == '\n') {
                cnt++;
                isonLine = false;  
            }
            text[i - pointer] = text[i];
        } 
        else {
            if (is_usless(text[i])) {
                pointer++;
            } 
            else {
                text[i - pointer] = text[i];
                isonLine = true;
            }
        }
    }

    for (int i = *len - pointer; i < *len; i++) {
        text[i] = '\0';
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