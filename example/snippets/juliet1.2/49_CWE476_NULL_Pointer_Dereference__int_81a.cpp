#include "CWE476_NULL_Pointer_Dereference__int_81.h"
namespace CWE476_NULL_Pointer_Dereference__int_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    const CWE476_NULL_Pointer_Dereference__int_81_base& baseObject = CWE476_NULL_Pointer_Dereference__int_81_goodG2B();
    baseObject.action(data);
}
#endif
}
