#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_delete_array_class_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twointsclass * data)
{
    {
        delete [] data;
    }
    data = new twointsclass;
    goodB2G1_sink(data);
}
#endif
}
