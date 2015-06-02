#include "std_testcase.h"
namespace CWE415_Double_Free__new_delete_array_struct_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(twoints * data)
{
    data = new twoints[100];
    delete [] data;
    goodB2G2_sink(data);
}
#endif
}
