#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>

char **get_cmd(char *cmd);
void execute_command(char* cmd);
void shell();