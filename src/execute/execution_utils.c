#include "../include/minishell.h"

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

	new_elem = malloc(sizeof(t_env_list));
	if (!new_elem)
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
	int			i;
	char		**str;
	t_env_list	*elem;

	elem = NULL;
	str = NULL;
	i = 0;
	if (!env)
		elem = ft_lstnew1((void **)str, TRUE);
	while (env[i])
	{
		str = ft_split(env[i], '=');
		ft_lstadd_back1(&elem, ft_lstnew1((void **)str, TRUE));
		free_split(str);
		i++;
	}
	return (elem);
}
