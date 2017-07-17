#include <wchar.h>
#include <string.h>
#include "std_testcase_io.h"
#include "std_testcase.h"

#define SRC_STRING "AAAAAAAAAA"
static int staticFive = 5;
static void goodG2B1()
{
    char * data;
    char dataGoodBuffer[10+1];
    if(staticFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        size_t i, sourceLen;
        sourceLen = strlen(source);
        for (i = 0; i < sourceLen + 1; i++)
        {
           /*@ slice pragma stmt; */
            data[i] = source[i];
        }
       
        printLine(data);
    }
}

void CWE121_Stack_Based_Buffer_Overflow__CWE193_char_declare_loop_07_good()
{
    goodG2B1();
}
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_declare_loop_07_good();
    printLine("Finished good()");
    return 0;
}
