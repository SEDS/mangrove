// Juliet CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__class_33.cpp
// Original structure: ref-ptr-read

// #################################################################
// ## Variant: ref-ptr-read_01
// ## CHANGE: Integer data allocated on stack
// #################################################################

#include <stdio.h>

int main(void)
{
    // CHANGE: Use integer data type instead of char.
    int * data;
    int * &dataRef = data;

    // CHANGE: Data allocated on stack
    // Cppcheck FP: (style) Variable 'dataBadBuffer' is assigned a value that is never used.
    int dataBadBuffer = 7;

    // CodeSonar FP: none
    // scan-build FP: (warning) Value stored to 'data' is never read
    // Cppcheck FP: (style) Variable 'data' is assigned a value that is never used.
    data = &dataBadBuffer;
    
    printf("int: %d\n", *dataRef);
    return 0;
}