#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_long_long_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    long long * data;
    map<int, long long *> data_map;
    free(data);
    data_map[1] = data;
}
#endif
}
