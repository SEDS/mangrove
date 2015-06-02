#include "CWE476_NULL_Pointer_Dereference__int_81.h"
namespace CWE476_NULL_Pointer_Dereference__int_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    const CWE476_NULL_Pointer_Dereference__int_81_base& o = CWE476_NULL_Pointer_Dereference__int_81_goodG2B();
    o.action(data);
}
#endif
}
