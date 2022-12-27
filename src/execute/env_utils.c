/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:42:00 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 14:19:09 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_envlstsize(t_env_list *lst)
{
	int			i;
	t_env_list	*crawler;

	crawler = lst;
	i = 0;
	while (crawler)
	{
		crawler = (*crawler).next;
		i++;
	}
	return (i);
}

char	**to_env(void)
{
	int			i;
	t_env_list	*env_lst;
	char		**env;
	int			size;
	char		*tmp;

	env_lst = g_data.env_lst;
	size = ft_envlstsize(env_lst) + 1;
	env = malloca(size * sizeof(char *));
	i = 0;
	while (env_lst)
	{
		tmp = ft_strjoin_alloca(env_lst->variable, "=", malloca);
		env[i] = ft_strjoin_alloca(tmp, env_lst->value, malloca);
		i++;
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

static char	*get_path(void)
{
	t_env_list	*env;

	env = g_data.env_lst;
	while (env)
	{
		if (!ft_strcmp(env->variable, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_cmd_path(t_cmd_lst *cmd)
{
	int		i;
	char	**path;
	char	*cmd_name;
	char	*tmp;

	path = ft_split(get_path(), ':');
	i = 0;
	cmd_name = cmd->cmd_name;
	if (cmd_name && *cmd_name)
	{
		while (path[i])
		{
			tmp = ft_strjoin_alloca(path[i], "/", malloca);
			tmp = ft_strjoin_alloca(tmp, cmd_name, malloca);
			if (access(tmp, F_OK) == 0)
			{
				cmd->cmd_name = tmp;
				return (free(path), TRUE);
			}
			i++;
		}
	}
	return (free(path), FALSE);
}
