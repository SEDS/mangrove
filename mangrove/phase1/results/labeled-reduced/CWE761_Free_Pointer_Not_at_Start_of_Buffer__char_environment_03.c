 #include <wchar.h>
#define ENV_VARIABLE "ADD"
#define GETENV getenv
#define SEARCH_CHAR 'S'
static void goodB2G2()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    data[0] = '\0';
    {
        size_t dataLen = strlen(data);
        char * environment = GETENV(ENV_VARIABLE);
        if (environment != NULL)
        {
            strncat(data+dataLen, environment, 100-dataLen-1);
        }
    }
    if(5==5)
    {
        {
            size_t i;
            for (i=0; i < strlen(data); i++)
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
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_environment_03_good();
    printLine("Finished good()");
     0;
}
/* Warning description
The left operand of '==' is a garbage value------                if (data[i] == SEARCH_CHAR)
*/

--fp-r--