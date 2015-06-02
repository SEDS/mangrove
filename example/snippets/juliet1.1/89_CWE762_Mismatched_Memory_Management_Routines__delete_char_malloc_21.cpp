#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_char_malloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(char * data)
{
    {
        delete data;
    }
    data = (char *)malloc(100*sizeof(char));
    goodB2G1_sink(data);
}
#endif
}
