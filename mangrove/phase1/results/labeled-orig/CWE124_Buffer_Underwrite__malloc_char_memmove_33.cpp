/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE124_Buffer_Underwrite__malloc_char_memmove_33.cpp
Label Definition File: CWE124_Buffer_Underwrite__malloc.label.xml
Template File: sources-sink-33.tmpl.cpp
*/
/*
 * @description
 * CWE: 124 Buffer Underwrite
 * BadSource:  Set data pointer to before the allocated memory buffer
 * GoodSource: Set data pointer to the allocated memory buffer
 * Sinks: memmove
 *    BadSink : Copy string to data using memmove
 * Flow Variant: 33 Data flow: use of a C++ reference to data within the same function
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

namespace CWE124_Buffer_Underwrite__malloc_char_memmove_33
{

#ifndef OMITBAD

void bad()
{
    char * data;
    char * &dataRef = data;
    data = NULL;
    {
        char * dataBuffer = (char *)malloc(100*sizeof(char));
        memset(dataBuffer, 'A', 100-1);
        dataBuffer[100-1] = '\0';
        /* FLAW: Set data pointer to before the allocated memory buffer */
        data = dataBuffer - 8;
    }
    {
        char * data = dataRef;
        {
            char source[100];
            memset(source, 'C', 100-1); /* fill with 'C's */
            source[100-1] = '\0'; /* null terminate */
            /* POTENTIAL FLAW: Possibly copying data to memory before the destination buffer */
            memmove(data, source, 100*sizeof(char));
            /* Ensure the destination buffer is null terminated */
            data[100-1] = '\0';
            printLine(data);
            /* INCIDENTAL CWE-401: Memory Leak - data may not point to location
             * returned by malloc() so can't safely call free() on it */
        }
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2B()
{
    char * data;
    char * &dataRef = data;
    data = NULL;
    {
        char * dataBuffer = (char *)malloc(100*sizeof(char));
        memset(dataBuffer, 'A', 100-1);
        dataBuffer[100-1] = '\0';
        /* FIX: Set data pointer to the allocated memory buffer */
        data = dataBuffer;
    }
    {
        char * data = dataRef;
        {
            char source[100];
            memset(source, 'C', 100-1); /* fill with 'C's */
            source[100-1] = '\0'; /* null terminate */
            /* POTENTIAL FLAW: Possibly copying data to memory before the destination buffer */
            memmove(data, source, 100*sizeof(char));
            /* Ensure the destination buffer is null terminated */
            data[100-1] = '\0';
            printLine(data);
            /* INCIDENTAL CWE-401: Memory Leak - data may not point to location
             * returned by malloc() so can't safely call free() on it */
        }
    }
}

void good()
{
    goodG2B();
}

#endif /* OMITGOOD */

} /* close namespace */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */
#ifdef INCLUDEMAIN

using namespace CWE124_Buffer_Underwrite__malloc_char_memmove_33; /* so that we can use good and bad easily */

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
--tp-o--