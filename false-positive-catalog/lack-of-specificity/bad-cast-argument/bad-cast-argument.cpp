// Juliet CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__class_01.cpp
// Structure: lack-of-specificity/bad-cast-argument

#include <stdio.h>

class TwoIntsClass 
{
    public:
        int intOne;
        int intTwo;
};

int main(void)
{
    int dataBadBuffer = 100;
    void * data = &dataBadBuffer;

    // scan-build FP: (warning) Function call argument is an uninitialized value
    // Cppcheck FP: none
    printf("int: %d\n", (reinterpret_cast<TwoIntsClass *>(data))->intTwo);
}