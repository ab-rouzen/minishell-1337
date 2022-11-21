
#include "minishell.h"

void	ft_export(t_env_list *ms_env, char **cmd, t_env_list *ms_export)
{
	char **str;
	t_env_list *tmp;

	if (cmd[1])
	{
		printf ("%s\n", ft_strchr(cmd[1], '='));

		str = ft_split(cmd[1], '=');
		if (str[1] != NULL && ft_strchr(cmd[1], '='))
		{
			str[0] = ft_strjoin(str[0], "=");
			str[1] = ft_strjoin("\"", str[1]);
			str[1] = ft_strjoin(str[1], "\"");
		}
		ft_lstadd_back1(&ms_env, ft_lstnew1((void **)str));
	}
	tmp = ms_env;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env_list *ms_env)
{
	t_env_list *tmp;

	tmp = ms_env;
	while (tmp)
	{
		printf("%s%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
	
	char	*str;
	char	**cmd;
	int		check;
	t_env_list *ms_env;
	t_env_list *ms_export;

(void)ac;
(void)av;

	ms_export = ft_env(env);
	ms_env = ft_env(env);
	check = 0;
	while (1) 
	{
		printf("\033[0;36m ");
		printf("mini_shell=>");
		printf("\033[0m "); 
		str = readline("");
		cmd = ft_split(str, ' ');
		if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
			ft_echo(cmd);
		else if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
			ft_cd(cmd);
		else if (!ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")))
			ft_pwd(cmd);
		else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
			ft_export(ms_export, cmd, ms_env);
		else if (!ft_strncmp(cmd[0], "env", ft_strlen("env")))
			ft_print_env(ms_env);
		else
			printf("%s: command not found\n", str);
	}
	return 0;
}
