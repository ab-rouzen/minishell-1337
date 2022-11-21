
#include "minishell.h"

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
}

void	ft_pwd(char **cmd)
{
	char cwd[100000];

	(void)cmd;
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
		*lst = new;
}

t_env_list	*ft_lstnew1(void **content)
{
	t_env_list	*new_elem;

	if (!(new_elem = malloc(sizeof(t_env_list))))
		return (NULL);
	new_elem->variable = ft_strdup(content[0]);
	if (content[1] == NULL ) // segfault in that line whene add sgtrcher// find out whene to add "" if 

	{
		content[1] = ft_strdup("");
		content[1] = ft_strjoin("\"", content[1]);
		content[1] = ft_strjoin(content[1], "\"");
	}
	new_elem->value = ft_strdup(content[1]);
	new_elem->next = NULL;
	return (new_elem);
}

t_env_list	*ft_env(char **env)
{
	int i;
	char **str;
	t_env_list	*elem;
	

	elem = NULL;
	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		if (str[1])
			str[1] = ft_strjoin("=", str[1]);
		ft_lstadd_back1(&elem, ft_lstnew1((void **)str)); 
		i++;
	}
	return (elem);
}
