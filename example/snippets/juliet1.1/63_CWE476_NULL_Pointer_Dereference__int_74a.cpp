#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__int_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    map<int, int *> data_map;
    {
        int tmp = 5;
        data = &tmp;
    }
    data_map[0] = data;
}
#endif
}
