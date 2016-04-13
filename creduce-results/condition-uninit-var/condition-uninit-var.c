// Condition - uninitialized variable

#include <stdio.h>

static int staticTrue = 1;


int main(void) {
    char * data;
    if(staticTrue) {
        data = "a message";
    }
    /* FP: Uninitialized variable: data */
    // `data` will always be initialized since the condition variable
    // is never changed to make the condition false.
    printf("message: %s\n", data);
}