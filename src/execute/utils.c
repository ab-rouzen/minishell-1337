/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/12 20:43:32 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	p_open(char *file, int flags, int perm)
{
	int	filedes;

	filedes = open(file, flags, perm);
	if (filedes == -1)
		exit(EXIT_FAILURE);
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

void	get_cmd_path(t_list *cmd_lst)
{
	int		i;
	char	**path;
	char	*tmp;

	path = ft_split(get_path(), ':');
	i = 0;
	if (access(((t_cmd_lst*)cmd_lst->content)->cmd_name, F_OK) == 0)
		return ;
	while (path[i])
	{
		tmp = ft_strjoin_alloca(path[i], "/", malloca);
		tmp = ft_strjoin_alloca(tmp, ((t_cmd_lst*)cmd_lst\
		->content)->cmd_name, malloca);
		if (access(tmp, F_OK) == 0)
		{
			((t_cmd_lst*)cmd_lst->content)->cmd_name = tmp;
			free(path);
			return ;
		}
		i++;
	}
	free(path);
	((t_cmd_lst*)cmd_lst->content)->cmd_name = NULL;
}
