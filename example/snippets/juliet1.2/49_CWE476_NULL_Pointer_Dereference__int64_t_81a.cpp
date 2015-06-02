#include "CWE476_NULL_Pointer_Dereference__int64_t_81.h"
namespace CWE476_NULL_Pointer_Dereference__int64_t_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    const CWE476_NULL_Pointer_Dereference__int64_t_81_base& baseObject = CWE476_NULL_Pointer_Dereference__int64_t_81_goodG2B();
    baseObject.action(data);
}
#endif
}
