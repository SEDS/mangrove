// Branch selection

#include <stdio.h>

int main(void) {
    FILE * data;
    data = NULL;
    data = fopen("sample.txt", "w+");
    switch(5) {
    case 6:
        printf("File not closed.");
        break;
    default:
        /* Close file */
        if (data != NULL) {
            fclose(data);
        }
        break;
    }
    /* Resource leak: data */
    // File will be closed since the default case will execute,
    // so there is no resource leak.
}