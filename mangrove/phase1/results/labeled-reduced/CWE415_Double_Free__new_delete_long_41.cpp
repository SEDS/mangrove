#include <wchar.h>
static void goodB2GSink(long * data)
{
    ; 
}
static void goodB2G()
{
    long * data;
    data = NULL;
    data = new long;
    delete data;
    goodB2GSink(data);
}
/* Warning description
Use of memory after it is freed------    goodB2GSink(data);
*/

--fp-r--