#include "include.h"

int main(int argc, char **argv){
    char *buffer;
    size_t bufsize = 32;

    buffer = (char *) malloc (bufsize * sizeof(char));

    if (buffer == NULL) {
        printf("Unable to allocate buffer");
        exit(-1);
    }

    while(1) {
        printf(">> ");
        while(getline(&buffer, &bufsize, stdin) == 0);
        printf("%s", buffer);
        printf("\n");
    }

    return 0;
}