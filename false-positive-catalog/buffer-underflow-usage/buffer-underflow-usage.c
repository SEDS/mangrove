// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_01.c
// Structure: buffer-underflow-usage

#include <stdio.h>

#define BUFFER_SIZE 10

int main(void)
{
    char inputBuffer[BUFFER_SIZE] = "";

    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: (error) Buffer is accessed out of bounds.
    fgets(inputBuffer, BUFFER_SIZE, stdin);
    return 0;
}