// Juliet CWE590_Free_Memory_Not_on_Heap__delete_class_alloca_11.cpp
// Structure: conditional-null-ptr-external-function

#include <stdio.h>
#include <stdlib.h>

#include "std_testcase.h"

int main(void)
{
    int * myint = NULL;
    if(globalReturnsTrue())
    {
        myint = (int *)malloc(sizeof(int));
        *myint = 5;
    }

    // scan-build FP: (warning) Dereference of null pointer (loaded from variable 'myint')
    // Cppcheck FP: (error) Possible null pointer dereference: myint
    printf("int: %d\n", *myint);
    
    free(myint);
}
