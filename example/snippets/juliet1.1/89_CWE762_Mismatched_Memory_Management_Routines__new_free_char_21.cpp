#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__new_free_char_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(char * data)
{
    {
        free(data);
    }
    data = new char;
    goodB2G1_sink(data);
}
#endif
}
