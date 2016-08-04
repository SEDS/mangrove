// NOT derived from Juliet
// FP structure: one-step-allocation-initialization

#include <stdio.h>

int main(void)
{
    // NOTE: FP is flagged for all data types tested: int, char, short int, float.
    int * data = new int(7);

    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: (error) Memory is allocated but not initialized: data
    printf("int: %d\n", *data);

    delete data;
    return 0;
}