#include "std_testcase.h"
static void goodG2B()
{
    char * data;
    data = NULL;
    goto source;
source:
    {
        char * dataBuffer = (char *)malloc(100*sizeof(char));
        memset(dataBuffer, 'A', 100-1);
        dataBuffer[100-1] = '\0';
        data = dataBuffer;
    }
    {
        char dest[100];
        memset(dest, 'C', 100-1); 
        dest[100-1] = '\0'; 
        strncpy(dest, data, strlen(dest));
        dest[100-1] = '\0';
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE127_Buffer_Underread__malloc_char_ncpy_18_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------        dest[100-1] = '
*/

--tp-r--