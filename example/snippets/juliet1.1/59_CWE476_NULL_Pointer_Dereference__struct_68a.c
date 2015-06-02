#include "std_testcase.h"
twoints * CWE476_NULL_Pointer_Dereference__struct_68_goodG2B_data;
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__struct_68_goodG2B_data = data;
}
#endif
