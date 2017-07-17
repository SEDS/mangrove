 #include "std_testcase.h"
static int staticTrue = 1; 
static void goodG2B2()
{
    int * data;
    data = NULL; 
    if(staticTrue)
    {
        {
            int * dataBuffer = new int[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5;
                }
            }
            data = dataBuffer;
        }
    }
    printIntLine(data[0]);
    delete [] data;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------    printIntLine(data[0]);
*/

--fp-r--