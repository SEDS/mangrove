#include "std_testcase.h"
#include <map>
using namespace std;
namespace CWE415_Double_Free__malloc_free_char_74
{
#ifndef OMITGOOD
static void goodB2G()
{
    char * data;
    map<int, char *> dataMap;
    free(data);
    dataMap[2] = data;
}
#endif
}
