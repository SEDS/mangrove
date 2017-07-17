 #include "std_testcase.h"
static int staticFive = 5;
static void goodG2B2()
{
    TwoIntsClass * data;
    data = NULL; 
    if(staticFive==5)
    {
        {
            TwoIntsClass * dataBuffer = new TwoIntsClass;
            dataBuffer->intOne = 2;
            dataBuffer->intTwo = 2;
            data = dataBuffer;
        }
    }
    printIntLine(data->intOne);
    delete data;
}
/* Warning description
Access to field 'intOne' results in a dereference of a null pointer (loaded from variable 'data')------    printIntLine(data->intOne);
*/

--fp-r--