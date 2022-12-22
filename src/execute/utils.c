/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/22 13:31:29 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	p_open(char *file, int flags, int perm)
{
	int	filedes;

	filedes = open(file, flags, perm);
	if (filedes == -1)
		return (-1);
	return (filedes);
}

static char	*get_path(void)
{
	t_env_list *env;

	env = g_data.env_lst;
	while (env)
	{
		if (ft_strcmp(env->variable, "PATH") == 0)
			return(env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_cmd_path(t_list *cmd_lst)
{
	int		i;
	char	**path;
	char	*tmp;

	path = ft_split(get_path(), ':');
	i = 0;
	if (access(((t_cmd_lst*)cmd_lst->content)->cmd_name, F_OK) == 0)
		return (TRUE);
	while (path[i])
	{
		tmp = ft_strjoin_alloca(path[i], "/", malloca);
		tmp = ft_strjoin_alloca(tmp, ((t_cmd_lst*)cmd_lst\
		->content)->cmd_name, malloca);
		if (access(tmp, F_OK) == 0)
		{
			((t_cmd_lst*)cmd_lst->content)->cmd_name = tmp;
			return (free(path), TRUE);
		}
		i++;
	}
	//((t_cmd_lst*)cmd_lst->content)->cmd_name = NULL;
	return (free(path), FALSE);
}

int	check_cmd(t_bool status, t_list **cmd_lst)
{
	t_cmd_lst	*cmd;

	cmd = (t_cmd_lst*)(*cmd_lst)->content;
	if (status == FALSE)
	{
		*cmd_lst = (*cmd_lst)->next;
		if (get_redir_lst_heredoc_num(cmd->redir_lst))
				g_data.hdoc_cmd_no++;
		if (cmd->cmd_name == NULL)
			return (status);
		printf("%s: %s: command not found\n", SHELL_NAME, cmd->cmd_name);
		return (status);
	}
	return (status);
	//continue ;
}

// char **to_env()
// {
// 	int i;
// 	t_list	*env;

// 	env = g_data.env_lst;
// 	i = 0;
// 	while (env)
// 	{
		
// 	}
// }