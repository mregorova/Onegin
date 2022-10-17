#include <assert.h>
#include <stdio.h>

void swap (const void* a, const void* b, int sizeEl) {

    char buf = 0;

    for(int i = 0; i < sizeEl; i++) {
        buf = *((char*)a + i);
        *((char*)a + i) = *((char*)b + i);
        *((char*)b + i) = buf;
        
    }
}