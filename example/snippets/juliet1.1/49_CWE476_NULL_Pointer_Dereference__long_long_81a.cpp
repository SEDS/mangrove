#include "CWE476_NULL_Pointer_Dereference__long_long_81.h"
namespace CWE476_NULL_Pointer_Dereference__long_long_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    const CWE476_NULL_Pointer_Dereference__long_long_81_base& o = CWE476_NULL_Pointer_Dereference__long_long_81_goodG2B();
    o.action(data);
}
#endif
}
