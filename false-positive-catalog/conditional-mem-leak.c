// Juliet CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05.c
// Structure: conditional-mem-leak

#include <stdlib.h>

static int staticTrue = 1;

int main(void)
{
    char * data = (char *)malloc(10*sizeof(char));
    if(staticTrue)
    {
        free(data);
    }
    // scan-build FP: (warning) Potential leak of memory pointed to by 'data'
    // Cppcheck FP: (error) Memory leak: data
}