/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/09 21:02:44 by arouzen          ###   ########.fr       */
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

static char	*get_path(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->variable, "PATH") == 0)
			return(env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_cmd_path(t_list *cmd_lst, t_env_list *env)
{
	int		i;
	char	**path;
	char	*tmp;

	path = ft_split(get_path(env), ':');
	//printf("%s\n", path[0]);
	i = 0;
	if (access(((t_cmd_lst*)cmd_lst->content)->cmd_name, F_OK) == 0)
		return (((t_cmd_lst*)cmd_lst->content)->cmd_name);
	while (path[i])
	{
		tmp = ft_strjoin_alloca(path[i], "/", malloca);
		tmp = ft_strjoin_alloca(tmp, ((t_cmd_lst*)cmd_lst\
		->content)->cmd_name, malloca);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}
