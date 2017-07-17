 #include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static int staticTrue = 1; 
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(staticTrue)
    {
        data = new char[10+1];
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
        printLine(data);
        delete [] data;
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        strcpy(data, source);
*/

--fp-r--