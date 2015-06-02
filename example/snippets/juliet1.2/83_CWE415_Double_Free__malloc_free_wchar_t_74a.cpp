#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_wchar_t_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    wchar_t * data;
    map<int, wchar_t *> dataMap;
    free(data);
    dataMap[0] = data;
}
#endif
}
