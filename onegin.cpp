#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <cmath.h>
#include <sys\stat.h>

typedef char* String;    //string type(pointer to first character in string)
typedef struct {         
    String str;
    int    len;
} poemString;            //struct witch contains string and it's length 

void set (const String text, poemString* const arr, const int textlen, const int len);
int input(String* text, int* textlen, const char* file1, const char* file2);
int create_buf_read_lines(FILE *hamlet, const String text, const char* filename, int num);
void write_lines(const String text, const size_t filesize, const char *filename);
int compare_lines(const void *a, const void *b);
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

int input(String *text, int* textlen, const char* file1, const char* file2) {
    
    char *text = NULL;
    int nlines = 0;
    int num = 0;
    int filesize = 0;

    //char* filename = (char*) calloc(FILENAME_MAX, sizeof(char*));//
    char filename[] = "..\\hamlet.txt";                 //it's important to choose appropriate directory
    FILE *hamlet = fopen(filename, "r");
    assert(hamlet != NULL);

    char* str = (char*) calloc(filesize, sizeof(*str));

    nlines = create_buf_read_lines(hamlet, *text, file1, num);
    if (nlines >= 0) return 1;                                 //process error

    size_t nLines = symbol_amount(str, filesize, '\n');
    char** lineptr = (char**)calloc(nLines, sizeof(char*));
    
    split_str(*text, textlen);

    qsort(lineptr, num, sizeof(char), compare_lines);
    write_lines(*text, filesize, file2);
    fclose(hamlet);

    return 0;
}

bool is_usless (char ch) {                                          //make all \ symbols equivalent
    const char less[] = " \0\n\t\r*.";
    for (int i = 0; less[i] != '\0'; i++) {
        if (less[i] == ch) {
            return true;
        }
    }
    return false;
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

int compare_lines(const void *a, const void *b) {

    char arg1 = *(const char*)a;
    char arg2 = *(const char*)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;

    return 0;
}

int symbol_amount(char* str, const size_t filesize, const char symbol) {
    assert(str != nullptr);

    int nsymbols = 0;

    for(size_t i = 0; i < filesize; ++i) {
        if(*str++ == symbol) {
            ++nsymbols;
        }
    }

    return nsymbols;
}

//read lines:
int create_buf_read_lines(FILE *hamlet, String *text, const char* filename, int num, int* textlen) {

    //fstat(fileno(hamlet), &text);
    *textlen = round(out.st_size / sizeof(char));

    *text = (char*)calloc(*textlen, sizeof(char));
    assert (text != NULL);

    num = fread(*text, sizeof(char), *textlen, hamlet);

    return num;
}

//write lines:
void write_lines(String *text, const size_t filesize, const char *filename) {

    FILE *hamlet = fopen(filename, "w");
    assert(hamlet != NULL);

    fwrite(*text, sizeof(char), filesize, hamlet);
}

int main() {
    return 0;
}