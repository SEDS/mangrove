// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_01.c
// Structure: incomplete-buffer-use

#include <stdio.h> // stdin

int main(void)
{
    char inputBuffer[10] = "";
    // scan-build FP: None
    // Cppcheck FP: Error: Buffer is accessed out of bounds.
    fgets(inputBuffer, 10, stdin);
}