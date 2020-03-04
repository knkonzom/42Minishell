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

// Initializing the shell during startup.
void    init_shell()
{
    clear();
    // ---------------------------------------------------------
    printf("\n\n\n\n******************""************************");
    printf("\n\n\n\t****Minishell****"); 
    printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n*******************""***********************"); 
    // ---------------------------------------------------------
    char    *username = getenv("USER");
    // ---------------------------------------------------------
    printf("\n\n\nUser is: @%s", username);
    printf("\n");
    // ---------------------------------------------------------
    sleep(1);
    clear();
}

// Function to take input.
int     take_input(char *str)
{
    char    *buf;

    buf = readline("\n$> ");
    if (strlen(buf) != 0)
    {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    }
    else
    {
        return 1;
    }
}

// Funciton to print current working directory.
void    print_dir()
{
    char    cwd[1024];

    getcwd(cwd, sizeof(cwd));
    printf("Current working directory: %s", cwd);
}

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

// Help command
void    open_help()
{
    puts("\n----------------------------------------------------"
        "\n\t***Welcome to Shell Help***"
        "\n\tCopyright @ knkonzom"
        "\n\tUse shell at your own risk..."
        "\n\tList of supported commands:"
        "\n\t\t>cd"
        "\n\t\t>ls"
        "\n\t\t>exit"
        "\n\t\t>General commands available in UNIX shell"
        "\n\t\t>Pipe handling"
        "\n\t\t>Improper space handling"
        "\n-----------------------------------------------------");
    return;
}

// Function to execute builtin commands
int     own_cmd_handler(char **parsed)
{
    int     num_of_cmds = 4, i , switch_own_arg = 0;
    char    *list_of_cmds[num_of_cmds];
    char    *username;

    list_of_cmds[0] = "exit";
    list_of_cmds[1] = "cd";
    list_of_cmds[2] = "help";
    list_of_cmds[3] = "hello";

    for (i = 0; i < num_of_cmds; i++)
    {
        if (strcmp(parsed[0], list_of_cmds[i]) == 0)
        {
            switch_own_arg = i + 1;
            break;
        }
    }

    switch (switch_own_arg)
    {
    case 1:
        printf("Goodbye!\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return (1);
    case 3:
        open_help();
        return (1);
    case 4:
        username = getenv("USER");
        printf("\nHello %s. \nThis is Minishell.\n", username);
        return (1);
    default:
        break;
    }
    return (0);
}

// Function for finding pipe.
int     parse_pipe(char *str, char **piped_str)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        piped_str[i] = strsep(&str, "|");
        if (piped_str[i] == NULL)
        {
            break;
        }
    }
    if (piped_str[1] == NULL)
    {
        return (0); // Return 0 if no pipe is found.
    }
    else
    {
        return (1);
    }
}

// Function for parsing command words.
void    parse_space(char *str, char **parsed)
{
    int i;
    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int     process_string(char *str, char **parsed, char** parsedpipe)
{
    char    *piped_str[2];
    int     piped = 0;

    piped = parse_pipe(str, piped_str);
    if (piped)
    {
        parse_space(piped_str[0], parsed);
        parse_space(piped_str[1], parsedpipe);
    }
    else
    {
        parse_space(str, parsed);
    }
    if (own_cmd_handler(parsed))
        return 0;
    else
        return 1 + piped;
}

int     main()
{
    char    input_string[MAXCOM], *parsed_args[MAXLIST];
    char*   parsed_args_piped[MAXLIST];

    int     exec_flag = 0;

    init_shell();
    while (1)
    {
        print_dir(); // Printing shell line.
        if (take_input(input_string))
            continue;
        exec_flag = process_string(input_string, parsed_args, parsed_args_piped);
        if (exec_flag == 1)
            exec_args(parsed_args);
        if (exec_flag == 2)
            exec_piped_args(parsed_args, parsed_args_piped);
    }
    return (0);
}