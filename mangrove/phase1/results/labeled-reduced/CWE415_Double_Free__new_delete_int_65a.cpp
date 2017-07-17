#include <wchar.h>
void goodB2GSink(int * data);
static void goodB2G()
{
    int * data;
    void (*funcPtr) (int *) = goodB2GSink;
    data = NULL;
    data = new int;
    delete data;
    funcPtr(data);
}
/* Warning description
Use of memory after it is freed------    funcPtr(data);
*/

--up-r--