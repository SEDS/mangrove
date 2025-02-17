/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34.c
Label Definition File: CWE680_Integer_Overflow_to_Buffer_Overflow__malloc.label.xml
Template File: sources-sink-34.tmpl.c
*/
/*
 * @description
 * CWE: 680 Integer Overflow to Buffer Overflow
 * BadSource: fscanf Read data from the console using fscanf()
 * GoodSource: Small number greater than zero that will not cause an integer overflow in the sink
 * Sinks:
 *    BadSink : Attempt to allocate array using length value from source
 * Flow Variant: 34 Data flow: use of a union containing two methods of accessing the same data (within the same function)
 *
 * */

#include "std_testcase.h"

typedef union
{
    int unionFirst;
    int unionSecond;
} CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_unionType;

#ifndef OMITBAD

void CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_bad()
{
    int data;
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_unionType myUnion;
    /* Initialize data */
    data = -1;
    /* POTENTIAL FLAW: Read data from the console using fscanf() */
    fscanf(stdin, "%d", &data);
    myUnion.unionFirst = data;
    {
        int data = myUnion.unionSecond;
        {
            size_t i;
            int *intPointer;
            /* POTENTIAL FLAW: if data * sizeof(int) > SIZE_MAX, overflows to a small value
             * so that the for loop doing the initialization causes a buffer overflow */
            intPointer = (int*)malloc(data * sizeof(int));
            for (i = 0; i < (size_t)data; i++)
            {
                intPointer[i] = 0; /* Potentially writes beyond the boundary of intPointer */
            }
            printIntLine(intPointer[0]);
            free(intPointer);
        }
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2B()
{
    int data;
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_unionType myUnion;
    /* Initialize data */
    data = -1;
    /* FIX: Set data to a relatively small number greater than zero */
    data = 20;
    myUnion.unionFirst = data;
    {
        int data = myUnion.unionSecond;
        {
            size_t i;
            int *intPointer;
            /* POTENTIAL FLAW: if data * sizeof(int) > SIZE_MAX, overflows to a small value
             * so that the for loop doing the initialization causes a buffer overflow */
            intPointer = (int*)malloc(data * sizeof(int));
            for (i = 0; i < (size_t)data; i++)
            {
                intPointer[i] = 0; /* Potentially writes beyond the boundary of intPointer */
            }
            printIntLine(intPointer[0]);
            free(intPointer);
        }
    }
}

void CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */
#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
--tp-o--