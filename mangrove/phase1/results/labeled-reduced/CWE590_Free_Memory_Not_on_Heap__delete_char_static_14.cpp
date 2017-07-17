 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL; 
    if(globalFive==5)
    {
        {
            char * dataBuffer = new char;
            *dataBuffer = 'A';
            data = dataBuffer;
        }
    }
    printHexCharLine(*data);
    delete data;
}
/* Warning description
Dereference of null pointer (loaded from variable 'data')------    printHexCharLine(*data);
*/

--fp-r--