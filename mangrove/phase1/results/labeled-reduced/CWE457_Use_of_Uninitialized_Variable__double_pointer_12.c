 static void goodG2B()
{
    double * data;
    if(globalReturnsTrueOrFalse())
    {
        data = (double *)malloc(sizeof(double));
        *data = 5.0;
    }
    else
    {
        data = (double *)malloc(sizeof(double));
        *data = 5.0;
    }
    if(globalReturnsTrueOrFalse())
    {
        printDoubleLine(*data);
    }
    else
    {
        printDoubleLine(*data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printDoubleLine(*data);
*/

--tp-r--