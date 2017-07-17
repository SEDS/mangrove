#include "std_testcase.h"
static void goodG2B()
{
    twoIntsStruct * data;
    twoIntsStruct * *dataPtr1 = &data;
    twoIntsStruct * *dataPtr2 = &data;
    twoIntsStruct dataBadBuffer[50];
    twoIntsStruct dataGoodBuffer[100];
    {
        twoIntsStruct * data = *dataPtr1;
        data = dataGoodBuffer;
        *dataPtr1 = data;
    }
    {
        twoIntsStruct * data = *dataPtr2;
        {
            twoIntsStruct source[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    source[i].intOne = 0;
                    source[i].intOne = 0;
                }
            }
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    data[i] = source[i];
                }
                printStructLine(&data[0]);
            }
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE805_struct_declare_loop_32_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Assigned value is garbage or undefined------        twoIntsStruct * data = *dataPtr1;
*/

--tp-r--