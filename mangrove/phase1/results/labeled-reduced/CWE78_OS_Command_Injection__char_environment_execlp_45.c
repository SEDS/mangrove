#include <unistd.h>
#define COMMAND_INT_PATH "/bin/sh"
#define COMMAND_INT "sh"
#define COMMAND_ARG1 "ls"
#define COMMAND_ARG2 "-la"
#define COMMAND_ARG3 data
#define ENV_VARIABLE "ADD"
#define GETENV getenv
#define EXECLP execlp
static char * CWE78_OS_Command_Injection__char_environment_execlp_45_goodG2BData;
static void goodG2BSink()
{
    char * data = CWE78_OS_Command_Injection__char_environment_execlp_45_goodG2BData;
    EXECLP(COMMAND_INT, COMMAND_INT, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}
static void goodG2B()
{
    char * data;
    char dataBuffer[100] = "";
    data = dataBuffer;
    strcat(data, "*.*");
    CWE78_OS_Command_Injection__char_environment_execlp_45_goodG2BData = data;
    goodG2BSink();
}
void CWE78_OS_Command_Injection__char_environment_execlp_45_good()
{
    goodG2B();
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE78_OS_Command_Injection__char_environment_execlp_45_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Address of stack memory associated with local variable 'dataBuffer' is still referred to by the global variable 'CWE78_OS_Command_Injection__char_environment_execlp_45_goodG2BData' upon returning to the caller.  This will be a dangling reference------    goodG2BSink();
*/

--fp-r--