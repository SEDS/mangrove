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
    // scan-build FP: (warning) Assigned value is garbage or undefined
    // Cppcheck FP: none
    int myInt = reinterpret_cast<TwoIntsClass *>(data)->intTwo;
}