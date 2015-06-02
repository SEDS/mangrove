#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__long_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    map<int, long *> dataMap;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    dataMap[0] = data;
}
#endif
}
