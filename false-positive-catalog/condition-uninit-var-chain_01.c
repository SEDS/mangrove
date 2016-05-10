// Juliet CWE476_NULL_Pointer_Dereference__char_07.c
// Variant: condition-uninit-var-chain_01

// *** REQUIRES TEST CASE SUPPORT FILES ***

#include "std_testcase.h"
#include <stdio.h>

static int staticFive = 5;

int main(void)
{
    char * data;
    if(staticFive!=5)
    {
        // CHANGE: Removed call to externally defined function
    }
    else
    {
        data = "Good";
    }

    if(staticFive==5)
    {
        // scan-build FP: none
        // Cppcheck FP: none
        printf("%02x\n", data[0]);
    }
}