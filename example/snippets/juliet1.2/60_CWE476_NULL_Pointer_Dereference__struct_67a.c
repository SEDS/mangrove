#include "std_testcase.h"
typedef struct _CWE476_NULL_Pointer_Dereference__struct_67_structType
{
    twoIntsStruct * structFirst;
} CWE476_NULL_Pointer_Dereference__struct_67_structType;
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    CWE476_NULL_Pointer_Dereference__struct_67_structType myStruct;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    myStruct.structFirst = data;
}
#endif
