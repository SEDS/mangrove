#include "std_testcase.h"
static twoints * CWE476_NULL_Pointer_Dereference__struct_45_goodG2B_data;
#ifndef OMITGOOD
static void goodG2B_sink()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__struct_45_goodG2B_data = data;
}
#endif
