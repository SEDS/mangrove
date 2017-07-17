 #include "std_testcase.h"
static int goodG2B2Static = 0;
static char * goodG2B2Source(char * data)
{
    if(goodG2B2Static)
    {
        {
            char * dataBuffer = (char *)malloc(100*sizeof(char));
            memset(dataBuffer, 'A', 100-1);
            dataBuffer[100-1] = '\0';
            data = dataBuffer;
        }
    }
    return data;
}
static void goodG2B2()
{
    char * data;
    data = NULL;
    goodG2B2Static = 1; 
    data = goodG2B2Source(data);
    {
        char dest[100];
        memset(dest, 'C', 100-1); 
        dest[100-1] = '\0'; 
        memmove(dest, data, 100*sizeof(char));
        dest[100-1] = '\0';
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE127_Buffer_Underread__malloc_char_memmove_21_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------        dest[100-1] = '
*/

--tp-r--