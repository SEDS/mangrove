#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__strdup_delete_array_wchar_t_13
{
#ifndef OMITGOOD
static void goodB2G2()
{
    wchar_t * data;
    {
        data = new wchar_t[100];
        free(data);
    }
}
#endif
}
