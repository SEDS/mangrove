 #include "std_testcase.h"
static int staticFive = 5;
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(staticFive==5)
    {
        {
            char * dataBuffer = new char[100];
            memset(dataBuffer, 'A', 100-1);
            dataBuffer[100-1] = '\0';
            data = dataBuffer;
        }
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        memcpy(data, source, 100*sizeof(char));
        data[100-1] = '\0';
        printLine(data);
    }
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memcpy(data, source, 100*sizeof(char));
*/

--fp-r--