 #include "std_testcase.h"
static void goodG2B2()
{
    long * data;
    data = NULL; 
    if(globalTrue)
    {
        {
            long * dataBuffer = (long *)malloc(100*sizeof(long));
            if (dataBuffer == NULL)
            {
                printLine("malloc() failed");
                exit(1);
            }
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    free(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printLongLine(data[0]);
*/

--fp-r--