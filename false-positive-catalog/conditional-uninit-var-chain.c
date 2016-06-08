// Juliet CWE476_NULL_Pointer_Dereference__char_05.c
// Structure: conditional-uninit-var-chain

#include <stdio.h>

static int staticTrue = 1;
static int staticFalse = 0;


int main(void)
{
    char * data;
    if(staticFalse)
    {

    }
    else
    {
        data = "Good";
    }

    if(staticTrue)
    {
        // scan-build FP: (warning) Dereference of undefined pointer value
        // Cppcheck FP: none
        printf("data: %c\n", data[0]);
    }
}
