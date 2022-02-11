#include "include.h"
#include "history_stack.c"
int bg = 0, bg_process_number = 0;
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

void execute(char *command){
    push_command(command);
    char *parsed_command[SIZE];
    command[strcspn(command, "\n")] = 0;

    if(strchr(command, '|')){
        parse_command(command, SIZE);
    }
    else if(strcmp(command, "sair") == 0){
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(command, "ver") == 0){
        printf("UnBash version 1.0.0 (last updated: 07/02/2022) made by: github.com/alexandre-ss\n");
    }   
    else if(strcmp(command, "limpa") == 0){ 
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
    pid_t pid1;
    int status;

    if(pid < 0){
        printf("Erro ao criar processo filho!\n");
        return;
    }
    else if(pid == 0){
        if(execvp(command[0], command) < 0) printf("Erro ao executar comando!\n");
        exit(0);
    } //child process
    else if(!bg){         
        waitpid(pid, &status, 0);
        signal(SIGCHLD, SIG_IGN);
    }
    else {
        printf("Processo em background [%d] iniciado\n", bg_process_number++);
        waitpid(pid, &status, WNOHANG);
        printf("finished");
    }

}

void separate_args(char *command, char *parsed_command[]){
    int i;
    if(is_background(command)){
        command[strcspn(command, "&")] = 0;
    }

    for ( i = 0; i < SIZE; i++){
        parsed_command[i] = strsep(&command, " ");
        if(parsed_command[i] == NULL) break;
        if(strlen(parsed_command[i]) == 0) i--;
    }
}

void parse_command(char *command, size_t size){

    const char delimiter[2] = "|";
    char *parsed_command[2], *command1[size], *command2[size];
    int i, aux;

    for ( i = 0; i < 2; i++)
    {
        parsed_command[i] = strsep(&command, delimiter);
        if(parsed_command == NULL) break;

        for (int j = 0; j < SIZE; j++){
            switch (i){
                case 0:
                    command1[j] = strsep(&parsed_command[i], " ");
                    if(command1[j] == NULL) break;
                    if(strlen(command1[j]) == 0) j--;
                    break;
                case 1:
                    command2[j] = strsep(&parsed_command[i], " ");
                    if(command2[j] == NULL) break;
                    if(strlen(command2[j]) == 0) j--;
                    break;
                default:
                    break;
            }
        }
    }
    execute_pipe(command1, command2);    
}

void execute_pipe(char **command1, char **command2){
    int fd[2];
    pid_t pid1, pid2;

    pipe(fd);
    if((pid1 = fork()) == 0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        if(execvp(command1[0], command1) < 0){
            printf("Erro ao executar comando!\n");
            exit(0);
        }
    }
    if((pid2 = fork()) == 0){
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        if(execvp(command2[0], command2) < 0){
            printf("Erro ao executar comando!\n");
            exit(0);
        }
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

}

int is_background(char *command){
    int len = strlen(command);
    bg = command[len-1] == '&' ? 1 : 0;
    return bg;
}

/*
configurar unbshrc
redirecionar comandos
processamento de programa em lote
*/