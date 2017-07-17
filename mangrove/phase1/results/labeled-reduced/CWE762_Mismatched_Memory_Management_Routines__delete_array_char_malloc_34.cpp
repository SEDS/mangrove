#include "std_testcase.h"
typedef union
{
    char * unionFirst;
    char * unionSecond;
} unionType;
static void goodB2G()
{
    char * data;
    unionType myUnion;
    data = NULL;
    data = (char *)malloc(100*sizeof(char));
    myUnion.unionFirst = data;
    {
        char * data = myUnion.unionSecond;
        free(data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'myUnion.unionFirst'------        char * data = myUnion.unionSecond;
*/

--up-r--