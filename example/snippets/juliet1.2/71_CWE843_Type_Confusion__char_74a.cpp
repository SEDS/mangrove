#include <map>
using namespace std;
namespace CWE843_Type_Confusion__char_74
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
    dataMap[2] = data;
}
#endif
}
