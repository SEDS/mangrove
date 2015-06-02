#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_array_free_int_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(int * data)
{
    {
        free(data);
    }
    data = new int[100];
    goodB2G1_sink(data);
}
#endif
}
