// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_01.c
// Original structure: buffer-underflow-usage

// #################################################################
// ## Variant: buffer-underflow-usage_01
// ## CHANGE: Increase the length of the buffer's initial value
// ## to one less than the length of the value stored to the buffer.
// #################################################################

#include <stdio.h>

#define BUFFER_SIZE 10

int main(void)
{
    // CHANGE: Increase the length of the initial value to 9 
    // (one less than the length of the value stored to the buffer).
    char inputBuffer[BUFFER_SIZE] = "123456789";

    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: none
    fgets(inputBuffer, BUFFER_SIZE, stdin);
    return 0;
}