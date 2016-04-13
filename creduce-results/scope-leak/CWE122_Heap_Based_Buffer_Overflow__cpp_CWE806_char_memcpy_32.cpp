#include "std_testcase.h"
namespace CWE122_Heap_Based_Buffer_Overflow__cpp_CWE806_char_memcpy_32
{
static void goodG2B()
{
    char * data;
    char * *dataPtr1 = &data,  * *dataPtr2 = &data;
    data = new char[100];
    {
        char * data = *dataPtr1;
        memset(data, 'A', 50-1); 
        data[50-1] = '\0'; 
        *dataPtr1 = data;
    }
    {
        char * data = *dataPtr2;
        {
            char dest[50] = "";
            memcpy(dest, data, strlen(data)*sizeof(char));
            dest[50-1] = '\0'; 
            printLine(data);
            delete [] data;
        }
    }
}
} 
