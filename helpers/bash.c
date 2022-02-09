#include "include.h"
#include "history_stack.c"

void iniciar(){
    printf("\033[0;31m");
    printf("#############################################\n");
    printf("#                 UnBash                    #\n");
    printf("#Autor: Alexandre Santana Sousa             #\n");
    printf("#############################################\n");
    printf("\n");
    printf("\033[0m");
}

char* read_command_line(char *buffer, size_t bufsize){
    while(getline(&buffer, &bufsize, stdin) == 0);
    return buffer;
}

void name_and_current_directory(char *name, char *directory){
    printf("\033[0;32m");       
    printf("UnB - %s - %s >> ", name, directory);
    printf("\033[0m");
}

void parse_command(char *command, size_t size){

    const char delimiter[2] = "|";
    char *parsed_command[size];
    int i;

    for ( i = 0; i < 2; i++)
    {
        parsed_command[i] = strsep(&command, delimiter);
        if(parsed_command == NULL) break;
    }
    //// Após o parse do pipe, executar o comando. sugestao: criar func

}

void execute(char *command){
    push_command(command);
    char *parsed_command[SIZE];

    if(strchr(command, '|')){
        parse_command(command, SIZE);
    }
    if(strcmp(command, "sair\n") == 0){
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(command, "ver\n") == 0){
        printf("UnBash version 1.0.0 (last updated: 07/02/2022) made by: github.com/alexandre-ss\n");
    }   
    else if(strcmp(command, "limpa\n") == 0){ 
        system("clear");
    }
    else if(strncmp(command, "historico", 9) == 0){
        history_show(command);
    }
    else if(strncmp(command, "cd", 2) == 0){
        separate_args(command, parsed_command);
        if(chdir(parsed_command[1]) != 0) printf("Falha ao mudar diretório!\n");
    }
    else{
        separate_args(command, parsed_command);
        execute_with_args(parsed_command);
    }
}

void execute_with_args(char *command[]){
    pid_t pid = fork();

    if(pid < 0){
        printf("Erro ao criar processo filho!\n");
        return;
    }
    else if(pid == 0){
        if(execvp(command[0], command) < 0) printf("Erro ao executar comando!\n");
    } //child process
    else {
        int rc_wait = wait(NULL);
    }
}

void separate_args(char *command, char *parsed_command[]){
    int i;

    command[strcspn(command, "\n")] = 0;
    for ( i = 0; i < SIZE; i++){
        parsed_command[i] = strsep(&command, " ");
        if(parsed_command[i] == NULL) break;
        if(strlen(parsed_command[i]) == 0) i--;
    }
}