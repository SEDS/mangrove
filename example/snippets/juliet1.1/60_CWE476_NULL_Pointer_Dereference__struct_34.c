#include "std_testcase.h"
typedef union
{
    twoints * a;
} CWE476_NULL_Pointer_Dereference__struct_34_union_type;
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    CWE476_NULL_Pointer_Dereference__struct_34_union_type my_union;
    {
        twoints tmp;
        data = &tmp;
    }
    my_union.a = data;
}
#endif
