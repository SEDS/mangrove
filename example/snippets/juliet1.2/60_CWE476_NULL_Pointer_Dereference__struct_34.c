#include "std_testcase.h"
typedef union
{
    twoIntsStruct * unionFirst;
} CWE476_NULL_Pointer_Dereference__struct_34_unionType;
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    CWE476_NULL_Pointer_Dereference__struct_34_unionType myUnion;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    myUnion.unionFirst = data;
}
#endif
