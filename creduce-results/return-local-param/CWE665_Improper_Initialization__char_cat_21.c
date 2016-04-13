static int  goodG2B2Static = 0;
static char * goodG2B2Source(char * data)
{
    if(goodG2B2Static)
    {
        data[0] = '\0'; 
    }
    return data;
}
static void goodG2B2()
{
    char * data;
    char dataBuffer[100];
    data = dataBuffer;
    goodG2B2Static = 1; 
    data = goodG2B2Source(data);
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strcat(data, source);
        printLine(data);
    }
}
