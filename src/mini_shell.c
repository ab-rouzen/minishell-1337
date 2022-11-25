
#include "minishell.h"
char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(&s[start]))
		p = malloc((ft_strlen(&s[start]) + 1) * sizeof(char));
	else
		p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_export(char *str)
{
	char	**expo;
	int		i;
	int		j;
	int		x;

	i = -1;
	j = 0;
	x = 0;
	expo = malloc ((3) * sizeof(char *));
	if (!expo)
		return (NULL);
	expo[2] = NULL;
	expo[1] = ft_strdup("");
	while (str[++i])
		if (str[i] != '=')
			x++;
		else
		{
			expo[0] = ft_substr1(str, 0, x);
			j = 0;
			while (str[++i])
				j++;
			expo[1] = ft_substr1(str, x+1, j);
			return (expo);
		}
	expo[0] = ft_substr1(str, 0, x);
	return (expo);
}

int	ft_find_variable(t_env_list *ms_list, char **str, char *cmd, int i)
{
	if (!ft_strchr(cmd, '='))
	{
		while (ms_list)
		{

			if (!ft_strcmp(ms_list->variable, str[0]))
			{
				str[i] = ft_strdup(ms_list->value);
				return (1);
			}
			ms_list = ms_list->next;
		}
		ft_lstadd_back1(&ms_list, ft_lstnew1((void **)str, FALSE));
	}
	str[0] = ft_strtrim(str[0], "+");
	if (ft_strchr(cmd, '='))
	{
		while (ms_list)
		{
			if(ft_strcmp(ms_list->variable, str[0]) == 0)
			{
				if (i)
				{
					free(ms_list->value);
					ms_list->value = ft_strdup(str[1]);
					ms_list->exported = TRUE;
					return (1);
				}
				else
				{
					ms_list->value = ft_strdup(ft_strjoin(ms_list->value, str[1]));
					return (1);
				}
			}
			ms_list = ms_list->next;
		}
	}
	return(0);
}




void	ft_export(t_env_list *ms_export, char **cmd, t_env_list *ms_env)
{
	char **str;
	(void)ms_env;

	str = ft_split_export(cmd[1]);
	if (ft_strchr(cmd[1], '='))
	{
		if (str[0][ft_strlen(str[0]) - 1] == '+')
		{
			if (ft_find_variable(ms_export, str,cmd[1], 0) == 0)
			{
				ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str, TRUE));
				return ;
			}
		}
		else
			if (ft_find_variable(ms_export, str,cmd[1], 1) == 0)
			{
				ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str, TRUE));
				return ;
			}
	}
	else if (!ft_strchr(cmd[1], '='))
		if (ft_find_variable(ms_export, str,cmd[1], 1) == 0)
		{
			ft_lstadd_back1(&ms_export, ft_lstnew1((void **)str, FALSE));
			return ;
		}
}

void	ft_print_expo(t_env_list *ms_export, char *cmd)
{
	t_env_list *tmp;
 	tmp = ms_export;

	while (!ft_strcmp(cmd, "export") && tmp)
	{
		printf("declare -x ");
		if(tmp->exported == TRUE)
			printf("%s=\"%s\"\n", tmp->variable, tmp->value);
		else
			printf("%s%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
	while (!ft_strcmp(cmd, "env") && tmp)
	{
		if(tmp->exported == TRUE)
			printf("%s=%s\n", tmp->variable, tmp->value);
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
			ft_print_expo(ms_export, cmd[0]);
		else if (!ft_strcmp(cmd[0], "export"))
			ft_export(ms_export, cmd, ms_env);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_print_expo(ms_export, cmd[0]);
		else
			printf("%s: command not found\n", str);
	}
	return 0;
}
