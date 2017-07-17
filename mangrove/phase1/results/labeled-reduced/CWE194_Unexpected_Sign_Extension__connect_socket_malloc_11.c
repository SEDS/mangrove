 static void goodG2B2()
{
    short data;
    data = 0;
    if(globalReturnsTrue())
    {
        data = 100-1;
    }
    if (data < 100)
    {
        char * dataBuffer = (char *)malloc(data);
        memset(dataBuffer, 'A', data-1);
        dataBuffer[data-1] = '\0';
        printLine(dataBuffer);
        free(dataBuffer);
    }
}
/* Warning description
Call to 'malloc' has an allocation size of 0 bytes------        char * dataBuffer = (char *)malloc(data);
*/

--fp-r--