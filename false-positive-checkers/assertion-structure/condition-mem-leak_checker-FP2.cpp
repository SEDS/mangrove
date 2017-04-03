// Juliet: CWE416_Use_After_Free__new_delete_array_char_07.cpp

#include "std_testcase.h"
static int staticFive = 5;

int main()
{
    char * data = NULL;
    // condition-mem-leak pattern flagged (false positive)
    // scan-build FP: none
    // Cppcheck FP: none
    if(staticFive==5)
    {
        // Moving this allocation statement before the `if` statement introduces the 
        // FP for both Cppcheck and scan-build.
        data = new char[100];
        delete [] data;
    }
}
