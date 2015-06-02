#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_array_free_struct_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twoints * data)
{
    {
        free(data);
    }
    data = new twoints[100];
    goodB2G1_sink(data);
}
#endif
}
