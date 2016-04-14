#include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static const int STATIC_CONST_TRUE = 1;
namespace CWE122_Heap_Based_Buffer_Overflow__cpp_CWE193_char_cpy_04
{
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(STATIC_CONST_TRUE)
    {
        data = new char[10+1];
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
        delete [] data;
    }
}
void good()
{
    goodG2B2();
}
}
using namespace CWE122_Heap_Based_Buffer_Overflow__cpp_CWE193_char_cpy_04;
int main(int argc, char * argv[])
{
    good();
    return 0;
}