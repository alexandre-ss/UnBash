#include "include.h"

int is_full() {
    if(top == MAXSIZE){
        return 1;
    }
    else {
        return 0;
    }
}

int push_command(char *command){
    if(!is_full()){
        top += 1;
        strcpy(history[top],command);
    }
    else{
        for(int i = 0; i < MAXSIZE; i++){
            strcpy(history[i],history[i+1]);
        }
        strcpy(history[top],command);
    }
}


void history_show(char *command){
    if((strlen(command) == strlen("historico x\n"))){ 
        int index = command[10] - 48;
        if(index >= 0 && index <= 9){
            execute(history[index]);
        }
        else {
            printf("Erro: índice fora do alcance do histórico!\n");
        }
    }
    else{
        for(int i = 0; i < top; i++){
            printf("[%d] %s", i, history[i]);
        }
    }
}
