// Juliet CWE476_NULL_Pointer_Dereference__class_34.cpp
// Structure: union-simultaneous-access

#include <stdio.h>

// Note: The data types of the union's members have been simplified from user-
// defined classes to integers.
typedef union
{
    int * firstMember;
    int * secondMember;
} unionType;

int main(void)
{
    unionType myUnion;
    int * myClass = new int();
    myUnion.firstMember = myClass;

    // CodeSonar FP: none
    // scan-build FP: (warning) Potential leak of memory pointed to by 'myUnion.firstMember'
    // Cppcheck FP: none
    int * myClass2 = myUnion.secondMember;
    delete myClass2;
    return 0;
}