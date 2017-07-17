#include "std_testcase.h"
void goodB2GSink_b(int64_t * data);
static void goodB2G()
{
    int64_t * data;
    data = NULL;
    data = new int64_t;
    delete data;
    goodB2GSink_b(data);
}
/* Warning description
Use of memory after it is freed------    goodB2GSink_b(data);
*/

--up-r--