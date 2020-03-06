#include "../includes/minishell.h"

// Function to execute system commands.
void    exec_args(char **parsed)
{
    // Forking a child process.
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child process...");
        return;
    }
    else if (pid == 0)
    {
        if (execvp(parsed[0], parsed) < 0)
        {
            printf("\nCould not execute command...");
        }
        exit(0);
    }
    else
    {
        // Wait for child process to terminate
        wait(NULL);
        return;
    }    
}