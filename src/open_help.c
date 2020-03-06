#include "../includes/minishell.h"

// Help command function
void    open_help()
{
    puts("\n----------------------------------------------------"
        "\n\tWelcome to Shell Help"
        // "\n\tCopyright @ knkonzom"
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