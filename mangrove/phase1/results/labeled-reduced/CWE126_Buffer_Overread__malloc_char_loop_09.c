 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (char *)malloc(100*sizeof(char));
        memset(data, 'A', 100-1); 
        data[100-1] = '\0'; 
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
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE126_Buffer_Overread__malloc_char_loop_09_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------            dest[i] = data[i];
*/

--fp-r--