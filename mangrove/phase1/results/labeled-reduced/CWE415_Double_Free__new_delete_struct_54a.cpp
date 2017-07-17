#include "std_testcase.h"
void goodB2GSink_b(twoIntsStruct * data);
static void goodB2G()
{
    twoIntsStruct * data;
    data = NULL;
    data = new twoIntsStruct;
    delete data;
    goodB2GSink_b(data);
}
/* Warning description
Use of memory after it is freed------    goodB2GSink_b(data);
*/

--up-r--