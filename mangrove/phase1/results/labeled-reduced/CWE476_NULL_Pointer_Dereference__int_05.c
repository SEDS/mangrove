#include <wchar.h>
static int staticTrue = 1; 
static int staticFalse = 0; 
static void goodB2G1()
{
    int * data;
    if(staticTrue)
    {
        data = NULL;
    }
    if(staticFalse)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        if (data != NULL)
        {
            printIntLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE476_NULL_Pointer_Dereference__int_05_good();
    printLine("Finished good()");
     0;
}
/* Warning description
The left operand of '!=' is a garbage value------        if (data != NULL)
*/
/* Warning description
Dereference of undefined pointer value------        printIntLine(*data);
*/

--fp-r--