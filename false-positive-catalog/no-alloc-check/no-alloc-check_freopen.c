// Juliet CWE675_Duplicate_Operations_on_Resource__freopen_43.cpp
// Structure: no-alloc-check_freopen (potentially a FP)

#include <stdio.h>

int main(void)
{
    // CodeSonar note: freopen() returns NULL.
    FILE * data = freopen("myfile.txt", "w+", stdin);

    // CodeSonar warning: Null Pointer Dereference. The body of fclose() dereferences 'data', but it is NULL.
    // scan-build warning: none
    // Cppcheck warning: none
    fclose(data);
    return 0;
}