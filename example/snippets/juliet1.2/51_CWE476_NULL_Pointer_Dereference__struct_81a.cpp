#include "CWE476_NULL_Pointer_Dereference__struct_81.h"
namespace CWE476_NULL_Pointer_Dereference__struct_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    const CWE476_NULL_Pointer_Dereference__struct_81_base& baseObject = CWE476_NULL_Pointer_Dereference__struct_81_goodG2B();
    baseObject.action(data);
}
#endif
}
