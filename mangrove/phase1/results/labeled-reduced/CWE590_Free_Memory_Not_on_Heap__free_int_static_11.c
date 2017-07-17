 #include <wchar.h>
static void goodG2B2()
{
    int * data;
    data = NULL; 
    if(globalReturnsTrue())
    {
        {
            int * dataBuffer = (int *)malloc(100*sizeof(int));
            if (dataBuffer == NULL)
            {
                printLine("malloc() failed");
                exit(1);
            }
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5;
                }
            }
            data = dataBuffer;
        }
    }
    printIntLine(data[0]);
    free(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE590_Free_Memory_Not_on_Heap__free_int_static_11_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printIntLine(data[0]);
*/

--fp-r--