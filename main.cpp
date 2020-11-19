#include "minish.h"

pid_t parent_pid;

void sig_int(int sig){
    print_sigint();
    if(getpid() != parent_pid){ // child -> running command in minish
        exit(0);
    }
}

void execute(char** args){
    int status;
    int pid = fork();
    if(pid < 0){
        perror("Cannot create child process");
        return;
    }
    if(pid == 0){ //child
        char location[500];
        strcpy(location, "/bin/");
        strcat(location, args[0]);
        int result = execvp(location, args);
        if(result == -1){
            perror("Cannot execute command (execvp error)");
            exit(1);
        }
        if(args[0] == "nano") exit(0); // To exit well after executing nano
    }
    else{
        pid_t waitPid = wait(&status);
        if(waitPid == -1){
            perror("Child process aborted");
            return;
        }
    }
}

void execute_command(char* cmd){
    char **args = NULL;
    args = get_cmd(cmd);
    if(args == NULL){
        return;
    }
    else if(strcmp(args[0], "quit") == 0){
        printf("Bye\n");
        exit(0);
    }
    else{
        if(args[0] != NULL){
            execute(args);
        }
    }
    free(args);
}

void print_string(char* str){
    printf("%s", str);
}

int main(){
    parent_pid = getpid();
    signal(SIGINT, sig_int);
    strcpy(pwd, getcwd(pwd, 500));
    strcat(pwd, "$ ");
    shell();
    return 0;
}