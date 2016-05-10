// Juliet CWE476_NULL_Pointer_Dereference__char_07.c
// Structure: condition-uninit-var-chain

// *** REQUIRES TEST CASE SUPPORT FILES ***

// *** Possibly just a more complicated version of the `condition-uninit-var` structure ***

#include "std_testcase.h"
#include <stdio.h>

static int staticFive = 5;

int main(void)
{
    char * data;
    if(staticFive!=5)
    {
        // This function call must be here for scan-build to give a FP.
        // Scan-build assumes this function sets staticFive to 5.
        printLine("shouldn't print");
    }
    else
    {
        data = "Good";
    }

    if(staticFive==5)
    {
        // scan-build FP: warning: Dereference of undefined pointer value
        // Cppcheck FP: none
        printf("%02x\n", data[0]);
    }
}