#include "read_and_comp.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

bool is_usless (char ch) {

    const char less[] = " \0\n\t\r*.";

    for (int i = 0; less[i] != '\0'; i++) {
        if (less[i] == ch) {
            return true;
        }
    }

    return false;
}

bool is_skipped (char ch) {

    const char less[] = "().,<>/?!!\"\n\t_:;'{}[]#1234567890�� -";

    for (int i = 0; less[i] != '\0'; i++) {
        if (less[i] == ch) {
            return true;
        }
    }

    return false;
}

int split_str (string const text, int* const len) {

    assert(text != NULL && "pointers mustn't be NULL");

    int delta = 0;
    int cnt   = 0;

    bool is_on_line = false;

    for (int i = 0; i < *len; i++) {

        if (is_on_line) {

            if (text[i] == '\0' || text[i] == '\n') {
                cnt++;
                is_on_line = false;  
            }
            text[i - delta] = text[i];
        } 

        else {

            if (is_usless(text[i])) {
                delta++;
            }

            else {
                text[i - delta] = text[i];
                is_on_line = true;
            }
        }
    }

    for (int i = *len - delta; i < *len; i++) {
        text[i] = '\0';
    }

    *len -= delta;

    return cnt;
}

void set (const string text, poem_string* const arr, const int textlen, const int len) {

    string charptr = text;
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

void input (const char* stream, string* text, poem_string** strarr, int* textlen, int* strarrlen) {
    
    FILE* file = fopen(stream, "r");
    assert(file != NULL && "No such file");

    struct stat out = {0};
    assert((fstat(fileno(file), &out) != -1) && "Error in file");
    *textlen = round(out.st_size / sizeof(char));

    *text = (string)calloc(*textlen, sizeof(char));

    assert(*text != NULL && "not enought memory");
    assert(*textlen <= (int)fread(*text, sizeof(char), *textlen, file) && "Error in input(not enought memory)");
    fclose(file);

    *strarrlen = split_str(*text, textlen);
    *strarr = (poem_string*)calloc(*strarrlen, sizeof(poem_string));
    
    assert(*strarr != NULL && "not enought memory");

    set(*text, *strarr, *textlen, *strarrlen);

}

void output (const char* stream, poem_string* strarr, int len) {

    FILE* file = fopen(stream, "a");
    assert(file != NULL && "error in file");
    
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < strarr[i].len; j++) {
            putc(strarr[i].str[j], file);
        }
        putc('\n', file);
    }

    fprintf(file, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    fclose(file);
}

void output_text (const char* stream, const string strarr) {
    FILE* file = fopen(stream, "a");
    assert(file != NULL && "error in file");
    fprintf(file, "%s\n\n", strarr);

    fclose(file);
}

int str_comp (const void* f_to_comp, const void* s_to_comp) {
    string f_to_comp_ = ((poem_string*)f_to_comp)->str;
    string s_to_comp_ = ((poem_string*)s_to_comp)->str;

    int f_to_comp_len = ((poem_string*)f_to_comp)->len;
    int s_to_comp_len = ((poem_string*)s_to_comp)->len;

    int f   = 0;
    int s   = 0;
    int buf = 0;

    while (is_skipped(f_to_comp_[f])) {
        f++;
    }
    while (is_skipped(s_to_comp_[s])) {
        s++;
    }

    while (f < f_to_comp_len && s < s_to_comp_len) {
        buf = tolower(f_to_comp_[f]) - tolower(s_to_comp_[s]);
        if (buf) {
            return buf;
        }
        f++;
        s++;
    }
    return f_to_comp_len - s_to_comp_len;
}

int str_comp_rev (const void* f_to_comp, const void* s_to_comp) {

    string f_to_comp_ = ((poem_string*)f_to_comp)->str;
    string s_to_comp_ = ((poem_string*)s_to_comp)->str;

    int f_to_comp_len = ((poem_string*)f_to_comp)->len;
    int s_to_comp_len = ((poem_string*)s_to_comp)->len;

    int f   = f_to_comp_len;
    int s   = s_to_comp_len;
    int buf = 0;

    while (is_skipped(f_to_comp_[f])) {
        f--;
    }
    while (is_skipped(s_to_comp_[s])) {
        s--;
    }

    while (f >= 0 && s >= 0) {
        buf = tolower(f_to_comp_[f]) - tolower(s_to_comp_[s]);
        if (buf) {
            return buf;
        }
        f--;
        s--;
    }
    return f_to_comp_len - s_to_comp_len;
}

void clear_file (const char* stream) {
    FILE* file = fopen(stream, "w");
    assert(file != NULL && "error in file");

    fclose(file);
}