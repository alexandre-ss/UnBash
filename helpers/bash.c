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
    int i = 0;

    parsed_command[i++] = strtok(command, delimiter);
    while (command != NULL)
    {
        parsed_command[i++] = strtok(NULL, delimiter);
    }  

    i = 0;
    while (parsed_command[i] != NULL){
        execute(parsed_command[i++]);
    }
}

void execute(char *command){
    if(strncmp(command, "ver",3) == 0) printf("UnBash version 1.0.0 (last updated: 07/02/2022) made by: github.com/alexandre-ss\n");
    if(strchr(command, '|')){
        parse_command(command, SIZE);
    }
    if(strncmp(command, "limpa",5) == 0) system("clear");
    if(strncmp(command, "historico",9) == 0) history_show(command);
    // add other if creating process etc
}

void history_stack(char *command){
    printf("%s\n", command);
    if(history_counter == 9){
        for(int i = 0; i <= history_counter; i++){
            history[i] = history[i+1];
        }
        history[history_counter] = command;
    }
    else {
        history[history_counter] = command;
        history_counter++;
    }
}

void history_show(char *command){
    if((strlen(command)-1) == strlen("historico x")){ 
       execute(history[10]);
    }
    else{
        for(int i = 0; i < history_counter; i++){
            printf("%s\n", history[i]);
        }
    }
}