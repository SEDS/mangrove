#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_free_long_long_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(long long * data)
{
    {
        free(data);
    }
    data = new long long;
    goodB2G1_sink(data);
}
#endif
}
