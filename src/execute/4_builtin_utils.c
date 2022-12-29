/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_builtin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:07:48 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 14:47:55 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_variable_norm(t_env_list *ms_list, char **str, char *cmd)
{
	char	*tmp;

	if (!ft_strchr(cmd, '='))
	{
		while (ms_list)
		{
			if (!ft_strcmp(ms_list->variable, str[0]))
			{
				free (str[1]);
				str[1] = ft_strdup(ms_list->value);
				return (1);
			}
			ms_list = ms_list->next;
		}
	}
	tmp = str[0];
	str[0] = ft_strtrim(str[0], "+");
	free(tmp);
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
				free(ms_list->value);
				ms_list->exported = TRUE;
				ms_list->value = ft_strjoin(ms_list->value, str[1]);
				return (1);
			}
			ms_list = ms_list->next;
		}
	}
	return (0);
}

int	ft_unset(t_env_list **head, char **cmd, int i)
{
	t_env_list	*prev;
	t_env_list	*tmp;
	t_env_list	**ms_list;

	while (cmd[++i])
	{
		prev = NULL;
		ms_list = head;
		while (*ms_list)
		{
			if (!ft_strcmp((*ms_list)->variable, cmd[i]))
			{
				tmp = *ms_list;
				if (prev == NULL)
					*ms_list = (*ms_list)->next;
				else
					prev->next = (*ms_list)->next;
				free_env_node(tmp);
				break ;
			}
			prev = *ms_list;
			ms_list = &(*ms_list)->next;
		}
	}
	return (0);
}

int	ft_check_is_num(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[0] == '-' || cmd[0] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_list *cmd_lst)
{
	char	**cmd;

	cmd = ((t_cmd_lst *)cmd_lst->content)->cmd_args;
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd[1])
	{
		if (ft_check_is_num(cmd[1]))
		{
			ft_putstr_fd("miishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_data.exit_status = 255;
		}
		else
			g_data.exit_status = ft_atoi(cmd[1]);
	}
	exit(g_data.exit_status);
	return (0);
}
