#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_array_long_long_realloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(long long * data)
{
    {
        delete [] data;
    }
    data = NULL;
    data = (long long *)realloc(data, 100*sizeof(long long));
    goodB2G1_sink(data);
}
#endif
}
