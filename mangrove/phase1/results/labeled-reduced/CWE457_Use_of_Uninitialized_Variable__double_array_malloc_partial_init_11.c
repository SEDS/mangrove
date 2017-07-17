 static void goodG2B2()
{
    double * data;
    data = (double *)malloc(10*sizeof(double));
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                data[i] = (double)i;
            }
        }
    }
    if(globalReturnsTrue())
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                printDoubleLine(data[i]);
            }
        }
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------}
*/

--tp-r--