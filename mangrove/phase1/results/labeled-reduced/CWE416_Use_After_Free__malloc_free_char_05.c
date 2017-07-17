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
    if(staticTrue)
    {
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE416_Use_After_Free__malloc_free_char_05_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------}
*/

--tp-r--