// Juliet CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__class_01.cpp
// Original structure: lack-of-specificity/bad-cast-argument

// #################################################################
// ## Variant: bad-cast-argument_02
// ## CHANGE: Assigned result of cast to variable
// #################################################################

#include <stdio.h>

class TwoIntsClass 
{
    public:
        int intOne;
        int intTwo;
};

int main(void)
{
    // Cppcheck FP: (style) Variable 'dataBadBuffer' is assigned a value that is never used.
    int dataBadBuffer = 100;
    void * data = &dataBadBuffer;

    // CHANGE: Store result of cast to a variable (instead of passing to a function)

    // CodeSonar error: Buffer Overrun. This code reads past the end of the buffer pointed to by 'data'.
    //   - 'data' evaluates to '&dataBadBuffer'.
    //   - The first byte read is at offset 4 from the beginning of the buffer pointed to by 'data', whose capacity is 4 bytes.
    //       - The offset exceeds the capacity.
    //   - The overrun occurs in stack memory.
    // scan-build error: (warning) Assigned value is garbage or undefined
    // Cppcheck error: none
    int myInt = reinterpret_cast<TwoIntsClass *>(data)->intTwo;
    return 0;
}