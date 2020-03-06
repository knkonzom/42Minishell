#include "../includes/minishell.h"

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