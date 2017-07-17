#include "std_testcase.h"
static void goodG2B1()
{
    long * data;
    data = NULL;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = new long;
        *data = 5L;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLine(*data);
    }
}
/* Warning description
Dereference of null pointer (loaded from variable 'data')------        printLongLine(*data);
*/

--fp-r--