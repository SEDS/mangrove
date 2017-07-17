#include "std_testcase.h"
static void goodB2G1()
{
    long * data;
    data = NULL;
    if(globalReturnsTrue())
    {
        data = (long *)malloc(100*sizeof(long));
    }
    if(globalReturnsFalse())
    {
        printLine("Benign, fixed string");
    }
    else
    {
        free(data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printLine("Benign, fixed string");
*/
--fp-r--