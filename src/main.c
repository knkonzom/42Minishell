#include "../includes/minishell.h"


// Driver program for minishell
int     main()
{
    char    input_string[MAXCOM], *parsed_args[MAXLIST];
    char*   parsed_args_piped[MAXLIST];

    int     exec_flag = 0;

    init_shell();
    while (1)
    {
        // print_dir(); // Printing shell line.
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