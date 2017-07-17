 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        {
            char * dataBuffer = new char[100];
            memset(dataBuffer, 'A', 100-1);
            dataBuffer[100-1] = '\0';
            data = dataBuffer;
        }
    }
    {
        char dest[100];
        memset(dest, 'C', 100-1); 
        dest[100-1] = '\0'; 
        memcpy(dest, data, 100*sizeof(char));
        dest[100-1] = '\0';
        printLine(dest);
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memcpy(dest, data, 100*sizeof(char));
*/

--fp-r--