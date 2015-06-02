#include "std_testcase.h"
#ifndef _WIN32
static void good2()
{
    {
        {
            wchar_t * data = (wchar_t *)malloc(100*sizeof(wchar_t));
            data = (wchar_t *)realloc(data, (130000)*sizeof(wchar_t));
        }
    }
}
#endif
