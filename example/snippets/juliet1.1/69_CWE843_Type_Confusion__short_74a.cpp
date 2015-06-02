#include <map>
using namespace std;
namespace CWE843_Type_Confusion__short_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    map<int, void *> data_map;
    {
        int buf = 8;
        data = &buf;
    }
    data_map[0] = data;
}
#endif
}
