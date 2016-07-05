// Juliet CWE672_Operation_on_Resource_After_Expiration_or_Release__list_int_14.cpp
// FP structure: clear-list

#include <list>
#include <stdio.h>

using namespace std;

int main(void)
{
    list<int> data;
    data.push_back(7);

    list<int> ::iterator i;
    for(i = data.begin(); i != data.end(); i++)
    {
        if (!*i)
        {
            data.clear();
        }
        // CodeSonar FP: Use After Free. The memory pointed to by *i was freed...and is read from here.
        // scan-build FP: none
        // Cppcheck FP: none
        printf("data: %d\n", *i);
    }
    return 0;
}