// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_cpy_05.c
// Structure: conditional-uninit-var

#include <stdlib.h>
#include <string.h>

static int staticTrue = 1;

int main(void)
{
    char * data;
    if (staticTrue)
    {
        // Cppcheck does not flag FP if malloc is used instead of alloca
        data = (char *)alloca((10)*sizeof(char));
    }
    // CodeSonar FP: none
    // scan-build FP: (warning) Function call argument is an uninitialized value
    // Cppcheck FP: (error) Uninitialized variable: data
    strcpy(data, "test");
    return 0;
}