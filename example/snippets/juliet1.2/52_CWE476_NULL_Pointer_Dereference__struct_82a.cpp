#include "CWE476_NULL_Pointer_Dereference__struct_82.h"
namespace CWE476_NULL_Pointer_Dereference__struct_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__struct_82_base* baseObject = new CWE476_NULL_Pointer_Dereference__struct_82_goodG2B;
    baseObject->action(data);
}
#endif
}
