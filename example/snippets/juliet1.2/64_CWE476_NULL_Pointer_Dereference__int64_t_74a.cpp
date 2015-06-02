#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__int64_t_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    map<int, int64_t *> dataMap;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    dataMap[1] = data;
}
#endif
}
