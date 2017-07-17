 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    char dataGoodBuffer[100];
    if(globalTrue)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        memmove(data, source, 100*sizeof(char));
        data[100-1] = '\0'; 
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE805_char_declare_memmove_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        memmove(data, source, 100*sizeof(char));
*/

--fp-r--