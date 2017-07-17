 #include "std_testcase.h"
static int staticTrue = 1; 
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(staticTrue)
    {
        data = (char *)malloc(100*sizeof(char));
        memset(data, 'A', 100-1); 
        data[100-1] = '\0'; 
    }
    {
        char dest[100];
        memset(dest, 'C', 100-1);
        dest[100-1] = '\0'; 
        memcpy(dest, data, strlen(dest)*sizeof(char));
        dest[100-1] = '\0';
        printLine(dest);
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE126_Buffer_Overread__malloc_char_memcpy_05_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memcpy(dest, data, strlen(dest)*sizeof(char));
*/

--fp-r--