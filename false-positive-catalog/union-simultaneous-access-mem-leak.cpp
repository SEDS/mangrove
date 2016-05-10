// Juliet CWE476_NULL_Pointer_Dereference__class_34.cpp
// Structure: union-simultaneous-access-mem-leak

#include <stdio.h>

class ClassType 
{
    public:
        int num;
};

typedef union
{
    ClassType * firstMember;
    ClassType * secondMember;
} unionType;


int main(void)
{
    unionType myUnion;
    ClassType * myClass = new ClassType();
    myUnion.firstMember = myClass;

    // scan-build FP: warning: Potential leak of memory pointed to by 'myUnion.firstMember'
    // Cppcheck FP: none
    ClassType * myClass2 = myUnion.secondMember;
    delete myClass2;
}