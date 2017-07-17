 static void goodG2B2()
{
    double * data;
    if(globalReturnsTrue())
    {
        data = (double *)malloc(sizeof(double));
        *data = 5.0;
    }
    if(globalReturnsTrue())
    {
        printDoubleLine(*data);
    }
}
/* Warning description
Dereference of undefined pointer value------        printDoubleLine(*data);
*/

--fp-r--