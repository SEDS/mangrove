 #include "std_testcase.h"
static int staticFive = 5;
static void goodG2B2()
{
    long * data;
    data = NULL; 
    if(staticFive==5)
    {
        {
            long * dataBuffer = new long;
            *dataBuffer = 5L;
            data = dataBuffer;
        }
    }
    printLongLine(*data);
    delete data;
}
/* Warning description
Dereference of null pointer (loaded from variable 'data')------    printLongLine(*data);
*/

--fp-r--