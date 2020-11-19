#include "minish.h"
char pwd[500];

char **get_cmd(char *cmd){
    char **args = NULL;
    args = (char **)malloc(10 * sizeof(char*));
    char *arg;
    int index = 0;
    if(args == NULL){
        perror("Cannot allocate memory\n");
        exit(1);
    }
    arg = strtok(cmd, " \t\r\n\a");
    if(arg == NULL) return NULL;
    while(arg != NULL){
        args[index] = arg;
        index++;
        arg = strtok(NULL, " \t\r\n\a");
    }
    args[index] = 0;
    return args;
}
/*
char** bar(char* str){
    char** args = NULL;
    args = (char**)malloc(10 * sizeof(char *));
    char *arg;
    int index = 0;
    if(args == NULL){
        perror("error malloc");
        exit(1);
    }
    arg = strtok(str, " \t\r\n\a");
    while(arg != NULL){
        args[index] = arg;
        index++;
        arg = strtok(NULL, " \t\r\n\a");
    }
    printf("%s", args[0]);
    return args;
}

void foo(char* str){
    printf("foo");
    char **args;
    args = bar(str);
}
*/

void execute_command(char* cmd){
    printf("exec_cmd");
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
        int i=0;
        while(args[i] != NULL){
            printf("%s\n", args[i]);
            i++;
        }
    }
    free(args);
}

void print_string(char* str){
    printf("%s", str);
}

void shell(){
    char *line = NULL;
    while(1){
        size_t len = 0;
        char shell_name[strlen(pwd) + 2];
        strcpy(shell_name, pwd);
        strcat(shell_name, "$ ");
        printf("\n%s", shell_name);
        if(getline(&line, &len, stdin) == -1){
            perror("Cannot read command line");
        }
        //foo(line);
        execute_command(line);
    }
}

int main(){
    strcpy(pwd, getcwd(pwd, 500));
    shell();
    return 0;
}