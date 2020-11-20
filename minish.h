#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <setjmp.h>

void print_sigint();
char **get_cmd(char *cmd);
void execute_command(char* cmd);
void shell();

extern char pwd[500];