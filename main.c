#include "helpers/include.h"
#include "helpers/bash.c"

int main(int argc, char **argv){
    char *buffer;
    size_t bufsize = 32;
    char cwd[PATH_MAX];
    char hostname[HOST_NAME_MAX+1];

    iniciar();
    while(1) {
        printf("\033[0;32m");       
        printf("UnB - %s - %s >> ",  getlogin(), getcwd(cwd, sizeof(cwd)));
        printf("\033[0m");

        buffer = (char *) malloc (bufsize * sizeof(char));
        if (buffer == NULL) {
            printf("Unable to allocate buffer");
            exit(-1);
        }

        ler_command_line(buffer, bufsize);

        free(buffer);
    }

    return 0;
}