// Juliet CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_file_01.c
// Structure: null-array-access

#include <stdlib.h>
#include <wchar.h>

int main(void)
{
    wchar_t * data = (wchar_t *)malloc(100*sizeof(wchar_t));
    data[0] = L'\0';

    size_t i;
    for (i=0; i < wcslen(data); i++)
    {
        // scan-build FP: (warning) Assigned value is garbage or undefined
        // Cppcheck FP: none
        wchar_t c = data[i];
    }
    free(data);
}
