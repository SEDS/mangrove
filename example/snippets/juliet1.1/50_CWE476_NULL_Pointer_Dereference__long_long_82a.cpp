#include "CWE476_NULL_Pointer_Dereference__long_long_82.h"
namespace CWE476_NULL_Pointer_Dereference__long_long_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__long_long_82_base* o = new CWE476_NULL_Pointer_Dereference__long_long_82_goodG2B;
    o->action(data);
}
#endif
}
