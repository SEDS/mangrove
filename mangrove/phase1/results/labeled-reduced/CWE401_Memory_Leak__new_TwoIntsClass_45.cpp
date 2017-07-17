#include "std_testcase.h"
static TwoIntsClass * goodG2BData;
static TwoIntsClass * goodB2GData;
static void goodG2BSink()
{
    ; 
}
static void goodG2B()
{
    TwoIntsClass * data;
    data = NULL;
    TwoIntsClass dataGoodBuffer;
    data = &dataGoodBuffer;
    data->intOne = 0;
    data->intTwo = 0;
    printIntLine(data->intOne);
    printIntLine(data->intTwo);
    goodG2BData = data;
    goodG2BSink();
}
static void goodB2GSink()
{
    TwoIntsClass * data = goodB2GData;
    delete data;
}
static void goodB2G()
{
    TwoIntsClass * data;
    data = NULL;
    data = new TwoIntsClass;
    data->intOne = 0;
    data->intTwo = 0;
    printIntLine(data->intOne);
    printIntLine(data->intTwo);
    goodB2GData = data;
    goodB2GSink();
}
void good()
{
    goodG2B();
    goodB2G();
}
/* Warning description
Address of stack memory associated with local variable 'dataGoodBuffer' is still referred to by the global variable 'goodG2BData' upon returning to the caller.  This will be a dangling reference------    goodG2BSink();
*/

--fp-r--