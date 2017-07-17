 #include "std_testcase.h"
static void goodG2B2()
{
    int64_t * data;
    data = NULL; 
    if(GLOBAL_CONST_FIVE==5)
    {
        {
            int64_t * dataBuffer = (int64_t *)malloc(100*sizeof(int64_t));
            if (dataBuffer == NULL)
            {
                printLine("malloc() failed");
                exit(1);
            }
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5LL;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLongLine(data[0]);
    free(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE590_Free_Memory_Not_on_Heap__free_int64_t_static_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printLongLongLine(data[0]);
*/

--fp-r--