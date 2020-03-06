#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXCOM 1000 // Max num of letters to be supported.
#define MAXLIST 100 // Max num of commands to be supported.

#define clear() printf("\033[H\033[J")

void    exec_args(char **parsed);
void    exec_piped_args(char **parsed, char **parsedpipe);
void    init_shell();
void    open_help();
void    parse_space(char *str, char **parsed);
void    print_dir();

int     own_cmd_handler(char **parsed);
int     parse_pipe(char *str, char **piped_str);
int     process_string(char *str, char **parsed, char** parsedpipe);
int     take_input(char *str);
