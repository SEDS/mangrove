#include "std_testcase.h"
typedef struct _CWE476_NULL_Pointer_Dereference__struct_67_struct_type
{
    twoints * a;
} CWE476_NULL_Pointer_Dereference__struct_67_struct_type;
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    CWE476_NULL_Pointer_Dereference__struct_67_struct_type my_struct;
    {
        twoints tmp;
        data = &tmp;
    }
    my_struct.a = data;
}
#endif
