#include "std_testcase.h"
namespace CWE416_Use_After_Free__new_delete_array_class_19
{
#ifndef OMITGOOD
static void goodG2B()
{
    twointsclass * data;
    data = new twointsclass[100];
    return;
}
#endif
}
