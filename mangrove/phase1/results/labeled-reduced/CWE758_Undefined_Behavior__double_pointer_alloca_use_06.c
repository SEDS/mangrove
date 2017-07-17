 #include "std_testcase.h"
static const int STATIC_CONST_FIVE = 5;
static void good2()
{
    if(STATIC_CONST_FIVE==5)
    {
        {
            double * data;
            double * * pointer = (double * *)ALLOCA(sizeof(double *));
            data = (double *)malloc(sizeof(double));
            *data = 5.0;
            *pointer = data; 
            {
                double * data = *pointer;
                printDoubleLine(*data);
            }
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE758_Undefined_Behavior__double_pointer_alloca_use_06_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------                printDoubleLine(*data);
*/

--tp-r--