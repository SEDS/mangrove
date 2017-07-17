#include "std_testcase.h"
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CLOSE_SOCKET close
#define SOCKET int
#define TCP_PORT 27015
#define IP_ADDRESS "127.0.0.1"
#define CHAR_ARRAY_SIZE (3 * sizeof(data) + 2)
static void goodG2B2()
{
    int data;
    data = -1;
    if(GLOBAL_CONST_FIVE==5)
    {
        data = 100-1;
    }
    {
        char source[100];
        char dest[100] = "";
        memset(source, 'A', 100-1);
        source[100-1] = '\0';
        if (data < 100)
        {
            strncpy(dest, source, data);
            dest[data] = '\0'; 
        }
        printLine(dest);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE195_Signed_to_Unsigned_Conversion_Error__connect_socket_strncpy_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Size argument is greater than the length of the destination buffer------            strncpy(dest, source, data);
*/

--fp-r--