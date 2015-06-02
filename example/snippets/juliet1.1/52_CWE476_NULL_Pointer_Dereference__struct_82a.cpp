#include "CWE476_NULL_Pointer_Dereference__struct_82.h"
namespace CWE476_NULL_Pointer_Dereference__struct_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__struct_82_base* o = new CWE476_NULL_Pointer_Dereference__struct_82_goodG2B;
    o->action(data);
}
#endif
}
