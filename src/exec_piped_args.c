#include "../includes/minishell.h"

// Function to execute piped system commands.
void    exec_piped_args(char **parsed, char **parsedpipe)
{
    // 0 is read end, 1 is write end.
    int     pipefd[2];
    pid_t   p1, p2;

    if (pipe(pipefd) < 0)
    {
        printf("\nError: pipe could not be initialized.");
        return;
    }

    p1 = fork();
    if (p1 < 0)
    {
        printf("\nError: could not fork.");
        return;
    }
    if (p1 == 0)
    {
        // Child 1 process executing.
        // Only write at the write end.
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(parsed[0], parsed) < 0)
        {
            printf("\nError: could not execute command 1.");
            exit(0);
        }
    }
    else
    {
        // Parent process executing.
        p2 = fork();
        
        if (p2 < 0)
        {
            printf("\nError: could not fork.");
            return;
        }

        // Child 2 process executing.
        // Only needs to read at read end.

        if (p2 == 0)
        {
            close(pipefd[1]);
            dup2(pipefd[0], STDOUT_FILENO);
            close(pipefd[0]);
            
            if (execvp(parsedpipe[0], parsedpipe) < 0)
            {
                printf("\nError: could not execute command 2.");
                exit(0);
            }
        }
        else
        {
            // Parent process executing, waiting for two children processes.
            wait(NULL);
            wait(NULL);
        }
    }
}