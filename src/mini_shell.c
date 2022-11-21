
#include "minishell.h"



int main(int ac, char **av, char **env)
{
	char *str;
	char **cmd;
(void)ac;
(void)av;
	while (1) 
	{
		printf("\033[0;36m ");
		printf("mini_shell=>");
		printf("\033[0m "); 
		str = readline("");
		cmd = ft_split(str, ' ');
		if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
			ft_cd(cmd);
		else if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")) == 0)
			ft_pwd(cmd);
		else if (ft_strncmp(cmd[0], "env", ft_strlen("env")) == 0)
			ft_env(env);
		// else if (ft_strncmp(cmd[0], "export", ft_strlen("export")) == 0)
		// 	ft_export(env);
		else
			printf("%s: command not found\n", str);
	}
	return 0;
}
