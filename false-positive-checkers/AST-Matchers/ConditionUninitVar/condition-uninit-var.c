// Juliet s01/CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_cpy_05.orig.c
// Structure: condition-uninit-var

#include <stdlib.h> // alloca
#include <string.h> // strcpy

static const int staticTrue = 1;

int main(void)
{
    char * dataGoodBuffer = (char *)alloca((10)*sizeof(char));
    char * data;
    if (staticTrue)
    {
           
        // Cppcheck does not flag FP if malloc is used instead of alloca
        data = dataGoodBuffer;
        //data = 0;
    }
    // scan-build FP: (warning) Function call argument is an uninitialized value
    // Cppcheck FP: (error) Uninitialized variable: data
    strcpy(data, "test");
}
