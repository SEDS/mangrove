#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__int_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    map<int, int *> dataMap;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    dataMap[1] = data;
}
#endif
}
