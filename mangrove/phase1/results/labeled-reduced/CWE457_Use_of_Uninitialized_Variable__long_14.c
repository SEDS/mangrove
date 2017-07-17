#include "std_testcase.h"
static void goodG2B1()
{
    long data;
    if(globalFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = 5L;
    }
    if(globalFive==5)
    {
        printLongLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE457_Use_of_Uninitialized_Variable__long_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        printLongLine(data);
*/

--fp-r--