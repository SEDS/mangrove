#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_delete_array_struct_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twoints * data)
{
    {
        delete [] data;
    }
    data = new twoints;
    goodB2G1_sink(data);
}
#endif
}
