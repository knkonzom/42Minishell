#include "../includes/minishell.h"

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