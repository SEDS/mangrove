#include "std_testcase.h"
namespace CWE476_NULL_Pointer_Dereference__struct_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    twoints * &data_ref = data;
    {
        twoints tmp;
        data = &tmp;
    }
    {
        twoints * data = data_ref;
    }
}
#endif
}
