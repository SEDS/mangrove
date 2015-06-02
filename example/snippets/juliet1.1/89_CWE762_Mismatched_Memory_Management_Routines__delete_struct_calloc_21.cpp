#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_struct_calloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twoints * data)
{
    {
        delete data;
    }
    data = (twoints *)calloc(100, sizeof(twoints));
    goodB2G1_sink(data);
}
#endif
}
