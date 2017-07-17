 #include "std_testcase.h"
static void goodB2G2()
{
    char * data;
    char * dataBadBuffer = (char *)malloc(sizeof(OneIntClass));
    if(1)
    {
        data = dataBadBuffer;
    }
    if(1)
    {
        {
            OneIntClass * classOne = new(data) OneIntClass;
            classOne->intOne = 5;
            printIntLine(classOne->intOne);
            free(data);
        }
    }
}
/* Warning description
Result of 'malloc' is converted to a pointer of type 'char', which is incompatible with sizeof operand type 'class OneIntClass'------    char * dataBadBuffer = (char *)malloc(sizeof(OneIntClass));
*/

--up-r--