 #include "std_testcase.h"
static void goodG2B2()
{
    int data;
    data = -1;
    if(globalTrue)
    {
        data = 100-1;
    }
    {
        char source[100];
        char dest[100] = "";
        memset(source, 'A', 100-1);
        source[100-1] = '\0';
        if (data < 100)
        {
            strncpy(dest, source, data);
            dest[data] = '\0'; 
        }
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE195_Signed_to_Unsigned_Conversion_Error__rand_strncpy_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Size argument is greater than the length of the destination buffer------            strncpy(dest, source, data);
*/

--fp-r--