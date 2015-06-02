#include "std_testcase.h"
#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__struct_52b_goodG2B_sink(twoints * data);
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__struct_52b_goodG2B_sink(data);
}
#endif
