#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_array_class_malloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twointsclass * data)
{
    {
        delete [] data;
    }
    data = (twointsclass *)malloc(100*sizeof(twointsclass));
    goodB2G1_sink(data);
}
#endif
}
