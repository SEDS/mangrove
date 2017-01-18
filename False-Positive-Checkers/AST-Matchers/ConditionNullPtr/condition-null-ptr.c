// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_05.c
// Structure: conditional-null-ptr

#include <stdlib.h>

static int staticTrue = 1;

int main(void)
{
    int * data = NULL;
    if(staticTrue)
    { 
        data = (int *)malloc(10*sizeof(int));
    }

    // CodeSonar FP: none
    // scan-build FP: (warning) Array access (from variable 'data') results in a null pointer dereference
    // Cppcheck: (error) Possible null pointer dereference: data
    data[0] = 5;
    free(data);
    return 0;
}
