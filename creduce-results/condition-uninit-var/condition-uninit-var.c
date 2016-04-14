#include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static int staticTrue = 1;
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA((10+1)*sizeof(char));
    if(staticTrue)
    {
        data = dataGoodBuffer;
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
    }
}
void CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_cpy_05_good()
{
    goodG2B2();
}
int main(int argc, char * argv[])
{
    CWE121_Stack_Based_Buffer_Overflow__CWE193_char_alloca_cpy_05_good();
    return 0;
}