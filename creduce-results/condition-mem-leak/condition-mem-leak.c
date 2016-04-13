// Condition - memory leak

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
/* The two variables below are not defined as "const", but are never
   assigned any other value, so a tool should be able to identify that
   reads of these will always return their initialized values. */
static int staticTrue = 1;


int main(void) {
    wchar_t * data;
    data = (wchar_t *)malloc(100*sizeof(wchar_t));
    wcscpy(data, L"This is some data");
    if (staticTrue) {
        free(data);
    }
    /* FP: Memory leak: data */
    // `data` is properly released since the condition clearly evaluates to true.
}