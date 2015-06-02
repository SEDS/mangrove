#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_int64_t_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    int64_t * data;
    map<int, int64_t *> dataMap;
    free(data);
    dataMap[0] = data;
}
#endif
}
