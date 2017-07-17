 #include "std_testcase.h"
static void goodG2B2()
{
    int64_t * data;
    data = NULL; 
    if(GLOBAL_CONST_FIVE==5)
    {
        {
            int64_t * dataBuffer = new int64_t[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5LL;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLongLine(data[0]);
    delete [] data;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printLongLongLine(data[0]);
*/

--fp-r--