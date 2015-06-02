#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__struct_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    map<int, twoIntsStruct *> dataMap;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    dataMap[0] = data;
}
#endif
}
