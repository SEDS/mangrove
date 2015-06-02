#include "std_testcase.h"
namespace CWE415_Double_Free__new_delete_array_class_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(twointsclass * data)
{
    data = new twointsclass[100];
    delete [] data;
    goodB2G2_sink(data);
}
#endif
}
