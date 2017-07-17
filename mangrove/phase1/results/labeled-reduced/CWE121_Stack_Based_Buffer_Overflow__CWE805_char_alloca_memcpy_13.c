#include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA(100*sizeof(char));
    if(GLOBAL_CONST_FIVE==5)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        memcpy(data, source, 100*sizeof(char));
        data[100-1] = '\0'; 
        printLine(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE805_char_alloca_memcpy_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------        memcpy(data, source, 100*sizeof(char));
*/

--fp-r--