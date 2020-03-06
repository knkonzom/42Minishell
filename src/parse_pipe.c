#include "../includes/minishell.h"

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