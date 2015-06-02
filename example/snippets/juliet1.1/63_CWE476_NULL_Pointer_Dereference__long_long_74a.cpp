#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__long_long_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    map<int, long long *> data_map;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    data_map[0] = data;
}
#endif
}
