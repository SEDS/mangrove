 #include "std_testcase.h"
static int staticFive = 5;
static void goodG2B2()
{
    int64_t * data;
    data = NULL;
    if(staticFive==5)
    {
        data = new int64_t[100];
    }
    {
        int64_t source[100] = {0}; 
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                data[i] = source[i];
            }
            printLongLongLine(data[0]);
            delete [] data;
        }
    }
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------                data[i] = source[i];
*/

--fp-r--