 #include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new char[10+1];
    }
    {
        char source[10+1] = SRC_STRING;
        strncpy(data, source, strlen(source) + 1);
        printLine(data);
        delete [] data;
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        strncpy(data, source, strlen(source) + 1);
*/

--fp-r--