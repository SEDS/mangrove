 #include "std_testcase.h"
static void goodG2B2()
{
    double * data;
    data = (double *)ALLOCA(10*sizeof(double));
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                data[i] = (double)i;
            }
        }
    }
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                printDoubleLine(data[i]);
            }
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE457_Use_of_Uninitialized_Variable__double_array_alloca_partial_init_11_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------                printDoubleLine(data[i]);
*/
--tp-r--