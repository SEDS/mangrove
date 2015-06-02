#include "std_testcase.h"
namespace CWE762_Mismatched_Memory_Management_Routines__strdup_delete_char_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(char * data)
{
    {
        delete data;
        char mystring[] = "mystring";
        data = strdup(mystring);
    }
    goodB2G1_sink(data);
}
#endif
}
