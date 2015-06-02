#ifndef OMITGOOD
static void good1()
{
    {
    {
        int intArray[5] = { 1, 2, 3, 4, 5 };
        char *charPointer = (char *)intArray;
        int toPrint = (int) (*(charPointer+(2*sizeof(int))));
    }
    }
}
#endif
