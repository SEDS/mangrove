#include "CWE476_NULL_Pointer_Dereference__long_82.h"
namespace CWE476_NULL_Pointer_Dereference__long_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__long_82_base* baseObject = new CWE476_NULL_Pointer_Dereference__long_82_goodG2B;
    baseObject->action(data);
}
#endif
}
