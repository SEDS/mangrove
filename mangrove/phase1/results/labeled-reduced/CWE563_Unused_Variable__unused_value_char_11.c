 static void goodB2G2()
{
    char data;
    if(globalReturnsTrue())
    {
        data = 'C';
    }
    if(globalReturnsTrue())
    {
        printHexCharLine(data);
    }
}
/* Warning description
Function call argument is an uninitialized value------        printHexCharLine(data);
*/

--fp-r--