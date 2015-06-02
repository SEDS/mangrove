#include "CWE476_NULL_Pointer_Dereference__int_82.h"
namespace CWE476_NULL_Pointer_Dereference__int_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__int_82_base* o = new CWE476_NULL_Pointer_Dereference__int_82_goodG2B;
    o->action(data);
}
#endif
}
