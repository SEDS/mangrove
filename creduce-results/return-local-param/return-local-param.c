#include <stdio.h>
#include <string.h>


char * respond(char * data) {
    // Modify the parameter and return pointer to it.
    strcat(data, " I am fine.");
    /* FP: Pointer to local array variable returned. */
    // The pointer still has meaning in the caller's scope.
    return data;
}


int main(void) {
    // Create a message
    char * message;
    char dataBuffer[100] = "How are you?";
    message = dataBuffer;
    // Modify the message
    message = respond(message);
}