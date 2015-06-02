#include "std_testcase.h"
typedef struct _CWE476_NULL_Pointer_Dereference__int64_t_67_structType
{
    int64_t * structFirst;
} CWE476_NULL_Pointer_Dereference__int64_t_67_structType;
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    CWE476_NULL_Pointer_Dereference__int64_t_67_structType myStruct;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    myStruct.structFirst = data;
}
#endif
