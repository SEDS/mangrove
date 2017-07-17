 #include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static void goodG2B2()
{
    char * data;
    char dataGoodBuffer[10+1];
    if(GLOBAL_CONST_TRUE)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        size_t i, sourceLen;
        sourceLen = strlen(source);
        for (i = 0; i < sourceLen + 1; i++)
        {
            data[i] = source[i];
        }
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_declare_loop_09_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of undefined pointer value------            data[i] = source[i];
*/

--fp-r--