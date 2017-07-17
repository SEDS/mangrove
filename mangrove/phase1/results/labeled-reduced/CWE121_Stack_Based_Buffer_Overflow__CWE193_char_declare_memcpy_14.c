 #include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static void goodG2B2()
{
    char * data;
    char dataGoodBuffer[10+1];
    if(globalFive==5)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        memcpy(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_declare_memcpy_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        memcpy(data, source, (strlen(source) + 1) * sizeof(char));
*/

--fp-r--