#include "helpers/include.h"
#include "helpers/bash.c"

int main(int argc, char **argv){
    char *command_buffer;
    size_t bufsize = 32;
    char cwd[PATH_MAX];
    char hostname[HOST_NAME_MAX+1];

    iniciar();
    while(1) {
        name_and_current_directory(getlogin(), getcwd(cwd, sizeof(cwd)));
        
        command_buffer = (char *) malloc (bufsize * sizeof(char));
        if (command_buffer == NULL) {
            printf("Unable to allocate command");
            exit(-1);
        }

        ler_command_line(command_buffer, bufsize);

        free(command_buffer);
    }

    return 0;
}