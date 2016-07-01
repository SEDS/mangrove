#include "AllocUsingProperty.h"

int main(void)
{
    AllocUsingProperty * myObject = new AllocUsingProperty();
    delete myObject;
    return 0;
}