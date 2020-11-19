#include "minish.h"

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