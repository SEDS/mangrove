// Juliet CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05.c
// Original structure: conditional-mem-leak

// #################################################################
// ## Variant: conditional-mem-leak_01
// ## CHANGE: Made global variable `const`
// #################################################################

#include <stdlib.h>

// CHANGE: Made global variable constant.
static const int staticTrue = 1;

int main(void)
{
    char * data = (char *)malloc(10*sizeof(char));
    if(staticTrue)
    {
        free(data);
    }
    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: none
    
    // Note: Adding a return statement here causes the Cppcheck FP to go away.
}