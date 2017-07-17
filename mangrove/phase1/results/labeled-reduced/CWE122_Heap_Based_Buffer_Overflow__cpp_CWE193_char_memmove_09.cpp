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
        memmove(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
        delete [] data;
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memmove(data, source, (strlen(source) + 1) * sizeof(char));
*/

--fp-r--