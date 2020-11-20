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

        int i, fd, status1;
        char *beforepipe[500], *afterpipe[500];
        pid_t pid1, pid2;
        for(i=0; args[i] != NULL; i++){
            if(!strcmp(args[i], "|")){ //pipe should be go first
                if(args[i]){
                    if(!args[i+1]){ // just execute first
                        args[i] = NULL;
                        break;
                    }
                    for(int j=0; j<i; j++){
                        beforepipe[j] = args[j];
                    }
                    for(int j=i+1; args[j] != NULL; j++){
                        afterpipe[j - i - 1] = args[j];
                    }

                    pid1 = fork();
                    if(pid1 < 0){
                        perror("Fork error");
                        exit(1);
                    }
                    else if(pid1 == 0){ // child
                        execute(beforepipe);
                        execute(afterpipe);
                    }
                    else{
                        pid_t waitPid = wait(&status1);
                        if(waitPid == -1){
                            perror("Child process aborted");
                            return;
                        }
                    }
                }
            }

            if(!strcmp(args[i], ">")){
                if(args[i]){
                    if(!args[i+1]){
                        perror("No file to redirect");
                        exit(1);
                    }
                    if((fd = open(args[i+1], O_RDWR|O_CREAT|S_IROTH, 0644)) == -1){
                        perror("Cannot open redirection file");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    args[i] = NULL;
                    args[i+1] = NULL;
                    for(; args[i] != NULL; i++){
                        args[i] = args[i+2];
                    }
                    args[i] = NULL;
                }
            }
        }

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