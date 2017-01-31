// Juliet CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05.c

#include <wchar.h>
#include <stdlib.h>

static const int staticTrue = 1;

static void goodB2G2()
{
    wchar_t * data;
    data = (wchar_t *)malloc(100*sizeof(wchar_t));
   
    if(staticTrue)
    {

       free(data); 
    }
    // scan-build FP: warning: Potential leak of memory pointed to by 'data'
    // Cppcheck FP: error: Memory leak: data

}


void CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05_good()
{
    goodB2G2();
}


int main(int argc, char * argv[])
{
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05_good();
    return 0;
}
