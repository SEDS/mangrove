 #include "std_testcase.h"
static void goodG2B2()
{
    long * data;
    data = NULL; 
    if(GLOBAL_CONST_TRUE)
    {
        {
            long * dataBuffer = new long[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    delete [] data;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printLongLine(data[0]);
*/

--fp-r--