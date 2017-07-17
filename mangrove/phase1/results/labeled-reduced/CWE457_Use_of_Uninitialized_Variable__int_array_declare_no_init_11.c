 static void goodG2B2()
{
    int * data;
    int dataUninitArray[10];
    data = dataUninitArray;
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                data[i] = i;
            }
        }
    }
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                printIntLine(data[i]);
            }
        }
    }
}
/* Warning description
Function call argument is an uninitialized value------                printIntLine(data[i]);
*/

--fp-r--