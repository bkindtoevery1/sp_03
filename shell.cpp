#include "minish.h"
#include "shell.h"

void shell(){
    char *line = NULL;
    while(1){
        shell_main:
        size_t len = 0;
        printf("%s", pwd);
        if(getline(&line, &len, stdin) == -1){
            perror("Cannot read command line");
        }
        //foo(line);
        execute_command(line);
    }
}