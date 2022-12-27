/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_builtin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:07:48 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 16:07:04 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_variable_norm(t_env_list *ms_list, char **str, char *cmd)
{
	if (!ft_strchr(cmd, '='))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, str[0]))
			{
				str[1] = ft_strdup(ms_list->value);
				return (1);
			}
			ms_list = ms_list->next;
		}
		ft_lstadd_back1(&ms_list, ft_lstnew1((void **)str, FALSE));
	}
	str[0] = ft_strtrim(str[0], "+");
	return (0);
}

int	ft_find_variable(t_env_list *ms_list, char **str, char *cmd, int i)
{
	if (ft_find_variable_norm(ms_list, str, cmd))
		return (1);
	if (ft_strchr(cmd, '='))
	{
		while (ms_list)
		{
			if (ft_strcmp(ms_list->variable, str[0]) == 0 && i)
			{
				free(ms_list->value);
				ms_list->value = ft_strdup(str[1]);
				ms_list->exported = TRUE;
				return (1);
			}
			else if (ft_strcmp(ms_list->variable, str[0]) == 0 && !i)
			{
				ms_list->exported = TRUE;
				ms_list->value = ft_strdup(ft_strjoin(ms_list->value, str[1]));
				return (1);
			}
			ms_list = ms_list->next;
		}
	}
	return (0);
}

int	ft_unset(t_env_list **ms_list, char **cmd)
{
	t_env_list	*prev;
	t_env_list	*tmp;
	int			i;

	i = 0;
	prev = NULL;
	while (cmd[++i])
	{
		ms_list = &(*ms_list);
		while (*ms_list)
		{
			if (!ft_strcmp((*ms_list)->variable, cmd[i]))
			{
				tmp = *ms_list;
				if (prev == NULL)
					*ms_list = (*ms_list)->next;
				else
					prev->next = (*ms_list)->next;
				free (tmp);
				break ;
			}
			prev = *ms_list;
			ms_list = &(*ms_list)->next;
		}
	}
	return (0);
}

int	ft_exit()
{
	
	return (0);
}
