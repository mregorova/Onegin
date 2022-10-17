#include "read_and_comp.h"

#include <stdlib.h>
#include <stdio.h>

const char* inputFile  = "hamletNormal.txt";
const char* outputFile = "output.txt";

int main () {
    string originaltext = NULL;
    poem_string* poem    = NULL;

    int textlen = 0;
    int poemLen = 0;
    

    input(inputFile, &originaltext, &poem, &textlen, &poemLen);
    clear_file(outputFile);

    qsort(poem, poemLen, sizeof(poem_string), str_comp);
    output(outputFile, poem, poemLen);

    output_text(outputFile, originaltext);

    return 0;
}