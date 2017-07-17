 #include "std_testcase.h"
static int staticTrue = 1; 
static void goodG2B2()
{
    int64_t * data;
    int64_t dataBadBuffer[50];
    int64_t dataGoodBuffer[100];
    if(staticTrue)
    {
        data = dataGoodBuffer;
    }
    {
        int64_t source[100] = {0}; 
        memmove(data, source, 100*sizeof(int64_t));
        printLongLongLine(data[0]);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE805_int64_t_declare_memmove_05_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        memmove(data, source, 100*sizeof(int64_t));
*/

--fp-r--