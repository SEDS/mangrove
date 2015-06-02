#include "CWE476_NULL_Pointer_Dereference__int64_t_82.h"
namespace CWE476_NULL_Pointer_Dereference__int64_t_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int64_t_82_base* baseObject = new CWE476_NULL_Pointer_Dereference__int64_t_82_goodG2B;
    baseObject->action(data);
}
#endif
}
