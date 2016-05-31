// NOT derived from Juliet
// FP structure: one-step-allocation-initialization

#include <stdio.h>

int main(void)
{
    int * data = new int(7);
    
    // scan-build FP: none
    // Cppcheck FP: (error) Memory is allocated but not initialized: data
    printf("int: %d\n", *data);

    delete data;
}