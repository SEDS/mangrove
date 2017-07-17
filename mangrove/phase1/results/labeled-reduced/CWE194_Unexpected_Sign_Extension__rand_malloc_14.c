 #include "std_testcase.h"
static void goodG2B2()
{
    short data;
    data = 0;
    if(globalFive==5)
    {
        data = 100-1;
    }
    if (data < 100)
    {
        char * dataBuffer = (char *)malloc(data);
        memset(dataBuffer, 'A', data-1);
        dataBuffer[data-1] = '\0';
        printLine(dataBuffer);
        free(dataBuffer);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE194_Unexpected_Sign_Extension__rand_malloc_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Call to 'malloc' has an allocation size of 0 bytes------        char * dataBuffer = (char *)malloc(data);
*/

--fp-r--