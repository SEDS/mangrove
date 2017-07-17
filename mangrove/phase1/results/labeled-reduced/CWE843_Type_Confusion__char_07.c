 #include "std_testcase.h"
static int staticFive = 5;
static void goodG2B2()
{
    void * data;
    data = NULL;
    if(staticFive==5)
    {
        {
            int intBuffer = 8;
            data = &intBuffer;
        }
    }
    printIntLine(*((int*)data));
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE843_Type_Confusion__char_07_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of null pointer------    printIntLine(*((int*)data));
*/

--fp-r--