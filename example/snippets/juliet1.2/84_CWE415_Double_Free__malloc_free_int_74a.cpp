#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_int_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    int * data;
    map<int, int *> dataMap;
    free(data);
    dataMap[1] = data;
}
#endif
}
