#include <wchar.h>
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
            free(data);
        }
    }
}
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05_good();
    printLine("Finished good()");
    return 0;
}