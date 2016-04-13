// Scope leak - memory leak flagged when combined only with nested scopes (no control structures) (FP possibly due to nested scopes or aliasing)

#include <stdio.h>
#include <string.h>

int main(void) {
    char * data;
    data = new char[100];

    // Pointer to pointer to manipulate the data.
    char * *dataPtr = &data;

	printf("test");

    delete [] *dataPtr;
    /* FP: Memory leak: data */
}