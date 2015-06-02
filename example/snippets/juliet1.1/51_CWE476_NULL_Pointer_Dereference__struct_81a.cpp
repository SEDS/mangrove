#include "CWE476_NULL_Pointer_Dereference__struct_81.h"
namespace CWE476_NULL_Pointer_Dereference__struct_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    const CWE476_NULL_Pointer_Dereference__struct_81_base& o = CWE476_NULL_Pointer_Dereference__struct_81_goodG2B();
    o.action(data);
}
#endif
}
