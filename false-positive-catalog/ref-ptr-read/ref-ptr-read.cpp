// Juliet CWE476_NULL_Pointer_Dereference__char_33.cpp
// Structure: ref-ptr-read

#include <stdio.h>

int main(void)
{
    char * data;
    char * &dataRef = data;

    // CodeSonar FP: none
    // scan-build FP: (warning) Value stored to 'data' is never read
    // Cppcheck FP: none
    data = "Good";
    printf("%c\n", dataRef[0]);
    return 0;
}