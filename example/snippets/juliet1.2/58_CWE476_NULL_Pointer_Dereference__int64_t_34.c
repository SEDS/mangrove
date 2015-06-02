#include "std_testcase.h"
typedef union
{
    int64_t * unionFirst;
} CWE476_NULL_Pointer_Dereference__int64_t_34_unionType;
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    CWE476_NULL_Pointer_Dereference__int64_t_34_unionType myUnion;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    myUnion.unionFirst = data;
}
#endif
