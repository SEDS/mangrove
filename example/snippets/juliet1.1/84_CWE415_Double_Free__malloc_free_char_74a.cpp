#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_char_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    char * data;
    map<int, char *> data_map;
    free(data);
    data_map[1] = data;
}
#endif
}
