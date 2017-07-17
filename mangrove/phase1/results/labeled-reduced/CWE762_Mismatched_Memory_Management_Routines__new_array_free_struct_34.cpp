#include "std_testcase.h"
typedef union
{
    twoIntsStruct * unionFirst;
    twoIntsStruct * unionSecond;
} unionType;
static void goodG2B()
{
    twoIntsStruct * data;
    unionType myUnion;
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    myUnion.unionFirst = data;
    {
        twoIntsStruct * data = myUnion.unionSecond;
        free(data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'myUnion.unionFirst'------        twoIntsStruct * data = myUnion.unionSecond;
*/

--up-r--