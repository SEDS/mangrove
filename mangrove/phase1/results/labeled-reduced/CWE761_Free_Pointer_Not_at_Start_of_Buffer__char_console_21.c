 #include "std_testcase.h"
#define SEARCH_CHAR 'S'
static int goodB2G2Static = 0;
static void goodB2G2Sink(char * data)
{
    if(goodB2G2Static)
    {
        {
            size_t i;
            for (i=0; i < strlen(data); i++)
            {
                if (data[i] == SEARCH_CHAR)
                {
                    printLine("We have a match!");
                    break;
                }
            }
            free(data);
        }
    }
}
static void goodB2G2()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    data[0] = '\0';
    {
        size_t dataLen = strlen(data);
        if (100-dataLen > 1)
        {
            if (fgets(data+dataLen, (int)(100-dataLen), stdin) != NULL)
            {
                dataLen = strlen(data);
                if (dataLen > 0 && data[dataLen-1] == '\n')
                {
                    data[dataLen-1] = '\0';
                }
            }
            else
            {
                printLine("fgets() failed");
                data[dataLen] = '\0';
            }
        }
    }
    goodB2G2Static = 1; 
    goodB2G2Sink(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_console_21_good();
    printLine("Finished good()");
     0;
}
/* Warning description
The left operand of '==' is a garbage value------                if (data[i] == SEARCH_CHAR)
*/
--fp-r--
