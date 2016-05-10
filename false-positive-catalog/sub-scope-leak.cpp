// Juliet s04/CWE122_Heap_Based_Buffer_Overflow__cpp_CWE806_char_memcpy_32.cpp
// Structure: sub-scope-leak

int main(void)
{
    char * data;
    data = new char[100];
    char * *dataPtr2 = &data;
    {
        char * data = *dataPtr2;
        delete [] data;
    }
    // scan-build FP: None
    // Cppcheck FP: error: Memory leak: data
}