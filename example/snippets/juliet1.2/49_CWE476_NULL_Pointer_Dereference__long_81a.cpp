#include "CWE476_NULL_Pointer_Dereference__long_81.h"
namespace CWE476_NULL_Pointer_Dereference__long_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    const CWE476_NULL_Pointer_Dereference__long_81_base& baseObject = CWE476_NULL_Pointer_Dereference__long_81_goodG2B();
    baseObject.action(data);
}
#endif
}
