// Juliet CWE590_Free_Memory_Not_on_Heap__delete_class_alloca_11.cpp
// Parent structure: function-conditional-null-ptr

// #################################################################
// ## Variant: function-conditional-null-ptr_01
// ## CHANGE: Function defined locally
// #################################################################

#include <stdio.h>
#include <stdlib.h>

// CHANGE: Define function locally (within this file) instead of in external file.
int globalReturnsTrue() 
{
    return 1;
}

int main(void)
{
    int * myint = NULL;
    if(globalReturnsTrue())
    {
        myint = (int *)malloc(sizeof(int));
        *myint = 5;
    }

    // scan-build FP: none
    // Cppcheck FP: (error) Possible null pointer dereference: myint
    printf("int: %d\n", *myint);
    
    free(myint);
}
