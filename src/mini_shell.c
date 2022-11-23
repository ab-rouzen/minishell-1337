
#include "minishell.h"

int	ft_find_variable(t_env_list *ms_list, char *variable, char *new_value, char *cmd)
{	
	if (!ft_strchr(cmd, '='))
		while (ms_list)
		{
			if(ft_strcmp(ms_list->variable, variable) == 0)
				return (1);
			ms_list = ms_list->next;
		}
	else
		while (ms_list)
		{
			if(ft_strcmp(ms_list->variable, variable) == 0)
			{
				ms_list->value = ft_strdup(new_value);
				return (1);
			}
			ms_list = ms_list->next;
		}
	return(0);
}


void	ft_export(t_env_list *ms_export, char **cmd, t_env_list *ms_env)
{
	char **str;
	t_env_list *tmp;
	if (cmd[1])
	{
		str = ft_split(cmd[1], '=');
		int i = 1;
		while (str[i] && str[i + 1])
		{
			str[1] = ft_strjoin(str[1], "=");
			str[1] = ft_strjoin(str[1], str[i + 1]);
			i++;
		}
		if (!str[1])
			str[1] = ft_strdup("");
	}
	if (cmd[1])
	{
		if (ft_strchr(cmd[1], '='))
		{
			str[1] = ft_strjoin("\"", str[1]);
			str[1] = ft_strjoin("=", str[1]);
			str[1] = ft_strjoin(str[1], "\"");
		}
		// if (!ft_strchr(cmd[1], '=') && !ft_find_variable(ms_export, str[0], str[1]))
		// 	ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str));

		if (ft_strchr(cmd[1], '='))
		{
			if (ft_find_variable(ms_export, str[0], str[1], cmd[1]))
						return ;
			if(ft_find_variable(ms_env, str[0], str[1], cmd[1]))
				return ;
			ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str));
			ft_lstadd_back1(&ms_env, ft_lstnew1((void **)str));
		}
		else if (ft_strchr(cmd[1], '=') == 0)
			if (ft_find_variable(ms_export, str[0], str[1], cmd[1]) == 0)
				ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str));
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

void	ft_print_expo(t_env_list *ms_export)
{
	t_env_list *tmp;
 	tmp = ms_export;

	while (tmp)
	{
		printf("declare -x ");
		if(ft_strchr(tmp->variable, '='))
			printf("%s\"%s\"\n", tmp->variable, tmp->value);
		else
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
		if (str && *str)
		{
			add_history(str);
		}
		cmd = ft_split(str, ' ');
		if (!ft_strcmp(cmd[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd[0], "cd"))
			ft_cd(cmd);
		else if (!ft_strcmp(cmd[0], "pwd"))
			ft_pwd(cmd);
		else if (!ft_strcmp(cmd[0], "export") && cmd[1] == NULL)
			ft_print_expo(ms_export);
		else if (!ft_strcmp(cmd[0], "export"))
			ft_export(ms_export, cmd, ms_env);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_print_env(ms_env);
		else
			printf("%s: command not found\n", str);
	}
	return 0;
}
