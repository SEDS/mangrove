#include "CWE476_NULL_Pointer_Dereference__int_82.h"
namespace CWE476_NULL_Pointer_Dereference__int_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int_82_base* baseObject = new CWE476_NULL_Pointer_Dereference__int_82_goodG2B;
    baseObject->action(data);
}
#endif
}
