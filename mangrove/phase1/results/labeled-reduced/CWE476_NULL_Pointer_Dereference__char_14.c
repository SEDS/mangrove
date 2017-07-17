#include "std_testcase.h"
static void goodG2B1()
{
    char * data;
    if(globalFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = "Good";
    }
    if(globalFive==5)
    {
        printHexCharLine(data[0]);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE476_NULL_Pointer_Dereference__char_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of undefined pointer value------        printHexCharLine(data[0]);
*/

--fp-r--