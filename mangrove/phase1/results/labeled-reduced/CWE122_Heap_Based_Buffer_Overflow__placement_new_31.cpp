 #include "std_testcase.h"
static void goodB2G()
{
    char * data;
    char * dataBadBuffer = (char *)malloc(sizeof(OneIntClass));
    data = dataBadBuffer;
    {
        char * dataCopy = data;
        char * data = dataCopy;
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
/* Warning description
Result of 'malloc' is converted to a pointer of type 'char', which is incompatible with sizeof operand type 'class TwoIntsClass'------    char * dataGoodBuffer = (char *)malloc(sizeof(TwoIntsClass));
*/
/* Warning description
Potential leak of memory pointed to by 'dataGoodBuffer'------    data = dataBadBuffer;
*/

--up-r--