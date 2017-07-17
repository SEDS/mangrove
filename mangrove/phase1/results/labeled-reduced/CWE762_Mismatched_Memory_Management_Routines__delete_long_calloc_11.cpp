#include "std_testcase.h"
static void goodB2G2()
{
    long * data;
    data = NULL;
    if(globalReturnsTrue())
    {
        data = (long *)calloc(100, sizeof(long));
    }
    if(globalReturnsTrue())
    {
        free(data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printLine("Benign, fixed string");
*/
--fp-r--