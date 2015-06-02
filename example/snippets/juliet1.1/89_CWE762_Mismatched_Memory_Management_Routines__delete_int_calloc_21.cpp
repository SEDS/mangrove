#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_int_calloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(int * data)
{
    {
        delete data;
    }
    data = (int *)calloc(100, sizeof(int));
    goodB2G1_sink(data);
}
#endif
}
