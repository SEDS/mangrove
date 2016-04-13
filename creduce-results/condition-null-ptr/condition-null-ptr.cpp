// Condition - null pointer dereference
// ** NOTE: Similar to `static-condition.c` case **

#include <stdio.h>
#include <string.h>

static const int STATIC_CONST_TRUE = 1;

int main(void) {
    char * data;
    data = NULL;
    if (STATIC_CONST_TRUE) {
        // Initialize data
        data = new char[10];
    }
    /* FP: Possible null pointer dereference: data */
    // `data` will not be NULL here since the the condition above is a constant TRUE value,
    // so `data` will be allocated memory.
    strcpy(data, "test");
    delete [] data;
}