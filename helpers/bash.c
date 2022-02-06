#include "include.h"
void iniciar(){
    printf("\033[0;31m");
    printf("#############################################\n");
    printf("#                 UnBash                    #\n");
    printf("#Autor: Alexandre Santana Sousa             #\n");
    printf("#############################################\n");
    printf("\n");
    printf("\033[0m");
}

void ler_command_line(char *buffer, size_t bufsize){
    while(getline(&buffer, &bufsize, stdin) == 0);
    printf("%s", buffer);
}

void name_and_current_directory(char *name, char *directory){
    printf("\033[0;32m");       
    printf("UnB - %s - %s >> ", name, directory);
    printf("\033[0m");
}