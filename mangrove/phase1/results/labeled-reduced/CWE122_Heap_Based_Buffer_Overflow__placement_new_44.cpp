 #include "std_testcase.h"
static void goodG2BSink(char * data)
{
    {
        TwoIntsClass * classTwo = new(data) TwoIntsClass;
        classTwo->intOne = 5;
        classTwo->intTwo = 10; 
        printIntLine(classTwo->intOne);
        free(data);
    }
}
static void goodG2B()
{
    char * data;
    void (*funcPtr) (char *) = goodG2BSink;
    char * dataGoodBuffer = (char *)malloc(sizeof(TwoIntsClass));
    data = dataGoodBuffer;
    funcPtr(data);
}
/* Warning description
Result of 'malloc' is converted to a pointer of type 'char', which is incompatible with sizeof operand type 'class TwoIntsClass'------    char * dataGoodBuffer = (char *)malloc(sizeof(TwoIntsClass));
*/

--up-r--