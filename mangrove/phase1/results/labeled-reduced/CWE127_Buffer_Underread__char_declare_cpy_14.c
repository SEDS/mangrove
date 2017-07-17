 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    char dataBuffer[100];
    memset(dataBuffer, 'A', 100-1);
    dataBuffer[100-1] = '\0';
    if(globalFive==5)
    {
        data = dataBuffer;
    }
    {
        char dest[100*2];
        memset(dest, 'C', 100*2-1); 
        dest[100*2-1] = '\0'; 
        strcpy(dest, data);
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE127_Buffer_Underread__char_declare_cpy_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        strcpy(dest, data);
*/

--fp-r--