 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    char dataBuffer[100];
    memset(dataBuffer, 'A', 100-1);
    dataBuffer[100-1] = '\0';
    if(GLOBAL_CONST_FIVE==5)
    {
        data = dataBuffer;
    }
    {
        size_t i;
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        for (i = 0; i < 100; i++)
        {
            data[i] = source[i];
        }
        data[100-1] = '\0';
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE124_Buffer_Underwrite__char_declare_loop_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of undefined pointer value------            data[i] = source[i];
*/

--fp-r--