// Modest buffer use

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int main() {
    int data = -1;
    // Initialize buffer with char array of length 14.
	char inputBuffer[BUFFER_SIZE] = "jake the snake";
	
	/* FP: Buffer is accessed out of bounds. */
	// Buffer is size 20 but is assumed to be only as long as the string it is initialized with in the line above.
	if (fgets(inputBuffer, BUFFER_SIZE, stdin) != NULL)	{
		data = atoi(inputBuffer);
		printf("integer read: %d\n", data);
	} else {
		printf("fgets() failed.\n");
	}
}