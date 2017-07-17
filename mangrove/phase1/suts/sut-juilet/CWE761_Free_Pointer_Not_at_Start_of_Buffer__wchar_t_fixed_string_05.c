#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "std_testcase_io.h"
#include "std_testcase.h"

#define BAD_SOURCE_FIXED_STRING L"Fixed String" 
#define SEARCH_CHAR L'S'
static int staticTrue = 1; 
static void goodB2G2()
{
    wchar_t * data;
    data = (wchar_t *)malloc(100*sizeof(wchar_t));
    data[0] = L'\0';
    wcscpy(data, BAD_SOURCE_FIXED_STRING);
    if(staticTrue)
    {
        {
            size_t i;
            for (i=0; i < wcslen(data); i++)
            {
                if (data[i] == SEARCH_CHAR)
                {
                    printLine("We have a match!");
                    break;
                }
            }
            free(data);
        }
    }
}
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    goodB2G2();
    printLine("Finished good()");
    return 0;
}
