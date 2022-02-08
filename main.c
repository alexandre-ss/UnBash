#include "helpers/include.h"
#include "helpers/bash.c"

int main(int argc, char **argv){
    char *command_buffer;
    char cwd[PATH_MAX];
    char hostname[HOST_NAME_MAX+1];

    iniciar();
    while(1) {
        name_and_current_directory(getlogin(), getcwd(cwd, sizeof(cwd)));
        
        command_buffer = (char *) malloc (SIZE * sizeof(char));
        if (command_buffer == NULL) {
            printf("Não foi possível alocar o comando!\n");
            exit(-1);
        }

        command_buffer = read_command_line(command_buffer, SIZE);
        execute(command_buffer);
        free(command_buffer);
    }

    return 0;
}
//////////////////////////////////// Retirar ponteiro de ponteiros