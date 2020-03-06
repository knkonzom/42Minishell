#include "../includes/minishell.h"

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
    printf("\n\n\nUsername: %s", username);
    printf("\n");
    // ---------------------------------------------------------
    sleep(1);
    clear();
}