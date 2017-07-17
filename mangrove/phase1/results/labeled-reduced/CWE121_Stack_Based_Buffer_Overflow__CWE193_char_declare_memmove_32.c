#define SRC_STRING "AAAAAAAAAA"
static void goodG2B()
{
    char * data;
    char * *dataPtr1 = &data;
    char * *dataPtr2 = &data;
    char dataGoodBuffer[10+1];
    {
        char * data = *dataPtr1;
        data = dataGoodBuffer;
        data[0] = '\0'; 
        *dataPtr1 = data;
    }
    {
        char * data = *dataPtr2;
        {
            char source[10+1] = SRC_STRING;
            memmove(data, source, (strlen(source) + 1) * sizeof(char));
            printLine(data);
        }
    }
}
/* Warning description
Assigned value is garbage or undefined------        char * data = *dataPtr1;
*/

--up-r--