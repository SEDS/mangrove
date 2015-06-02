#include <map>
using namespace std;
namespace CWE843_Type_Confusion__short_74
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    map<int, void *> dataMap;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    dataMap[1] = data;
}
#endif
}
