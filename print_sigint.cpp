#include "minish.h"
#include "print_sigint.h"

char pwd[500];

void print_sigint(){
    puts("Cannot killed by Ctrl+c");
    puts(pwd);
}