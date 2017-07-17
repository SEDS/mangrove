 #include "std_testcase.h"
static void goodG2B2()
{
    TwoIntsClass * data;
    data = NULL; 
    if(globalFive==5)
    {
        {
            TwoIntsClass * dataBuffer = new TwoIntsClass[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i].intOne = 1;
                    dataBuffer[i].intTwo = 1;
                }
            }
            data = dataBuffer;
        }
    }
    printIntLine(data[0].intOne);
    delete [] data;
}
/* Warning description
Dereference of null pointer------    printIntLine(data[0].intOne);
*/

--fp-r--