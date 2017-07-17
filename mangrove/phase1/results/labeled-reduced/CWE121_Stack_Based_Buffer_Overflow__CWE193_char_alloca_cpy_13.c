#include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA((10+1)*sizeof(char));
    if(GLOBAL_CONST_FIVE==5)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_cpy_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        strcpy(data, source);
*/

--fp-r--