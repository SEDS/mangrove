#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE476_NULL_Pointer_Dereference__struct_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    map<int, twoints *> data_map;
    {
        twoints tmp;
        data = &tmp;
    }
    data_map[1] = data;
}
#endif
}
