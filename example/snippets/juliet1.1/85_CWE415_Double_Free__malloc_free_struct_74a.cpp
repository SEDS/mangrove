#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_struct_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    twoints * data;
    map<int, twoints *> data_map;
    free(data);
    data_map[2] = data;
}
#endif
}
