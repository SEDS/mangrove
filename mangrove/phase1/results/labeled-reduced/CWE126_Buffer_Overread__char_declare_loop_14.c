 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    char dataBadBuffer[50];
    char dataGoodBuffer[100];
    memset(dataBadBuffer, 'A', 50-1); 
    dataBadBuffer[50-1] = '\0'; 
    memset(dataGoodBuffer, 'A', 100-1); 
    dataGoodBuffer[100-1] = '\0'; 
    if(globalFive==5)
    {
        data = dataGoodBuffer;
    }
    {
        size_t i, destLen;
        char dest[100];
        memset(dest, 'C', 100-1);
        dest[100-1] = '\0'; 
        destLen = strlen(dest);
        for (i = 0; i < destLen; i++)
        {
            dest[i] = data[i];
        }
        dest[100-1] = '\0';
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE126_Buffer_Overread__char_declare_loop_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of undefined pointer value------            dest[i] = data[i];
*/

--fp-r--