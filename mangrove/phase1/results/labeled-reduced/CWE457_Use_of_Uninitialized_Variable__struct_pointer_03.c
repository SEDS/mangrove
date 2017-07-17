 #include "std_testcase.h"
static void goodG2B2()
{
    twoIntsStruct * data;
    if(5==5)
    {
        data = (twoIntsStruct *)malloc(sizeof(twoIntsStruct));
        data->intOne = 5;
        data->intTwo = 6;
    }
    if(5==5)
    {
        printIntLine(data->intOne);
        printIntLine(data->intTwo);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE457_Use_of_Uninitialized_Variable__struct_pointer_03_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printIntLine(data->intTwo);
*/

--tp-r--