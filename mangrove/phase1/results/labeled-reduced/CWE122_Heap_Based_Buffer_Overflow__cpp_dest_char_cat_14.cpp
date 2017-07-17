 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(globalFive==5)
    {
        data = new char[100];
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strcat(data, source);
        printLine(data);
        delete [] data;
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        strcat(data, source);
*/

--fp-r--