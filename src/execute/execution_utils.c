
#include "../include/minishell.h"

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

void	ft_update_export(t_env_list *ms_list, char* oldpwd)
{
	char cwd[100000];

	getcwd(cwd, sizeof(cwd));
	while (ms_list)
	{
		if (!ft_strcmp(ms_list->variable, "PWD"))
			ms_list->value = ft_strdup((const char*)cwd);
		if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			ms_list->value = ft_strdup(oldpwd);
		ms_list = ms_list->next;
	}
}

void	ft_cd(char **cmd, t_env_list *ms_list)
{
	char cwd[100000];

	getcwd(cwd, sizeof(cwd));
	if (!cmd[1] || !(ft_strcmp(cmd[1],"~")))
	{
		chdir("/Users/imittous");
		ft_update_export(ms_list, cwd);
	}
	else if (!(ft_strcmp(cmd[1],"-")))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, "OLDPWD"))
			{
				printf("%s\n", ms_list->value);
				chdir(ms_list->value);
				ft_update_export(ms_list, cwd);
				return ;
			}
			ms_list = ms_list->next;
		}
		printf ("mini_shell: cd: OLDPWD not set");
	}
	else if (chdir(cmd[1]) < 0)
		printf ("mini_shell: cd: %s: No such file or directory\n", cmd[1]);
	else
		ft_update_export(ms_list, cwd);
}

void	ft_pwd()
{
	char cwd[100000];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}


t_env_list	*ft_lstlast1(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back1(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	last = ft_lstlast1(*lst);
	if (last && new)
		last->next = new;
	else
	{
		*lst = new;
	}
}

t_env_list	*ft_lstnew1(void **content, t_bool exported)
{
	t_env_list	*new_elem;
	if (!(new_elem = malloc(sizeof(t_env_list))))
		return (NULL);
	if (content != NULL)
	{
		new_elem->variable = ft_strdup(content[0]);

		if (content[1] == NULL)
			content[1] = ft_strdup("");
		new_elem->value = ft_strdup(content[1]);
		new_elem->exported = exported;
		new_elem->next = NULL;
	}
	return (new_elem);
}
t_env_list	*ft_env(char **env)
{
	int i;
	char **str = NULL;
	t_env_list	*elem;
	

	elem = NULL;
	i = 0;
	if (!env)
	{
		elem = ft_lstnew1((void **)str, TRUE);
	}
	while (env[i])
	{
		str = ft_split(env[i], '=');
		ft_lstadd_back1(&elem, ft_lstnew1((void **)str, TRUE)); 
		i++;
	}
	return (elem);
}
