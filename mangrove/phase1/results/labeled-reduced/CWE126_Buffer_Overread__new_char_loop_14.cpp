 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(globalFive==5)
    {
        data = new char[100];
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
        delete [] data;
    }
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------            dest[i] = data[i];
*/

--fp-r--