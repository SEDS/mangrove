 #include "std_testcase.h"
static int staticTrue = 1; 
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(staticTrue)
    {
        data = new char[100];
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strcpy(data, source);
        printLine(data);
        delete [] data;
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        strcpy(data, source);
*/

--fp-r--