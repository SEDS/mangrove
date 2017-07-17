 static void goodG2B2()
{
    int * data;
    int * dataGoodBuffer = (int *)ALLOCA(100*sizeof(int));
    if(globalReturnsTrue())
    {
        data = dataGoodBuffer;
    }
    {
        int source[100] = {0}; 
        memmove(data, source, 100*sizeof(int));
        printIntLine(data[0]);
    }
}
/* Warning description
Function call argument is an uninitialized value------        memmove(data, source, 100*sizeof(int));
*/

--fp-r--