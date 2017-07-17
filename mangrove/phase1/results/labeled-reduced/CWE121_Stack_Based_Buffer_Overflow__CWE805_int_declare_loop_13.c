 #include "std_testcase.h"
static void goodG2B2()
{
    int * data;
    int dataGoodBuffer[100];
    if(GLOBAL_CONST_FIVE==5)
    {
        data = dataGoodBuffer;
    }
    {
        int source[100] = {0}; 
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                data[i] = source[i];
            }
            printIntLine(data[0]);
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE805_int_declare_loop_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of undefined pointer value------                data[i] = source[i];
*/

--fp-r--