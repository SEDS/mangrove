#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__delete_array_char_realloc_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(char * data)
{
    {
        delete [] data;
    }
    data = NULL;
    data = (char *)realloc(data, 100*sizeof(char));
    goodB2G1_sink(data);
}
#endif
}
