#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_free_wchar_t_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(wchar_t * data)
{
    {
        free(data);
    }
    data = new wchar_t;
    goodB2G1_sink(data);
}
#endif
}
