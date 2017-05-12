// Juliet CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_10.c

#include <stdlib.h>
#include <wchar.h>

 // MAINTENANCE NOTE: This string must contain the SEARCH_CHAR 
#define BAD_SOURCE_FIXED_STRING L"Fixed String"
#define SEARCH_CHAR L'S'

int globalTrue = 1;

int main() {
    wchar_t * data = (wchar_t *)malloc(100*sizeof(wchar_t));
    data[0] = L'\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    wcscpy(data, BAD_SOURCE_FIXED_STRING);
    if(globalTrue) {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != L'\0'; data++)
        {
        }
        free(data);
    }
}