#include "../includes/minishell.h"

// Funciton to print current working directory.
void    print_dir()
{
    char    cwd[1024];

    getcwd(cwd, sizeof(cwd));
    printf("Current working directory: %s", cwd);
}