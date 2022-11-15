
#include "../minishell.h"

int main()
{
    char *str;
    char **cmd;
    int i;
    while (1) 
    {
        printf("mini_shell> ");
        str = readline("-> ");
        
            cmd = ft_split(str, ' ');
        if (ft_memcmp(cmd[0], "echo", 4) == 0)
        {
            i = 1;
            while (cmd[i])
                printf ("%s ", cmd[i++]);
            printf ("\n");
        }
    }
    return 0;
}