#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_class_calloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(twointsclass * data)
{
    {
        delete data;
    }
    data = (twointsclass *)calloc(100, sizeof(twointsclass));
    goodB2G1_sink(data);
}
#endif
}
