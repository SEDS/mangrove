#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_array_wchar_t_malloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(wchar_t * data)
{
    {
        delete [] data;
    }
    data = (wchar_t *)malloc(100*sizeof(wchar_t));
    goodB2G1_sink(data);
}
#endif
}
