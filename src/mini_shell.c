
#include "../minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	j = 0;
	check = 0;
	if (cmd[i] && cmd[i][j] == '-')
	{
		j++;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			check = 1;
			i++;
		}
	}
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i] != NULL)
			printf (" ");
	}
	if (check == 0)
		printf("\n");
}

void	ft_cd(char **cmd)
{
	if (chdir(cmd[1]) < 0)
		printf ("mini_shell: cd: %s: No such file or directory\n", cmd[1]);
	else
		chdir(cmd[1]);
}

void	ft_cd(char **cmd)
{
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", cwd);
}



int main()
{
	char *str;
	char **cmd;
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
		else
		{
			printf("%s: command not found\n", str);
			free(str);
		}
	}
	return 0;
}