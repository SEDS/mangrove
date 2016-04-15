#include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static const int STATIC_CONST_TRUE = 1;
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
int main(int argc, char * argv[])
{
    good();
    return 0;
}
