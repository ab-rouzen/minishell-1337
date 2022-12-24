/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 13:09:52 by arouzen          ###   ########.fr       */
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
		if (!ft_strcmp(env->variable, "PATH"))
			return(env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_cmd_path(t_list *cmd_lst)
{
	int		i;
	char	**path;
	char	*cmd_name;
	char	*tmp;

	path = ft_split(get_path(), ':');
	i = 0;
	cmd_name = ((t_cmd_lst*)cmd_lst->content)->cmd_name;
	if (access(cmd_name, F_OK) == 0)
		return (TRUE);
	if (cmd_name && *cmd_name)
		while (path[i])
		{
			tmp = ft_strjoin_alloca(path[i], "/", malloca);
			tmp = ft_strjoin_alloca(tmp, cmd_name, malloca);
			if (access(tmp, F_OK) == 0)
			{
				((t_cmd_lst*)cmd_lst->content)->cmd_name = tmp;
				//printf("accessed here: %s\n", tmp);
				return (free(path), TRUE);
			}
			i++;
		}
	return (free(path), FALSE);
}

int	check_cmd(t_bool status, t_list **cmd_lst)
{
	t_cmd_lst	*cmd;

	cmd = (t_cmd_lst*)(*cmd_lst)->content;
	if (status == FALSE)
	{
		//*cmd_lst = (*cmd_lst)->next;
		// if (get_redir_lst_heredoc_num(cmd->redir_lst))
		// 	g_data.hdoc_cmd_no++;
		if (cmd->cmd_name == NULL)
			return (FALSE);
		printf("%s: %s: command not found\n", SHELL_NAME, cmd->cmd_name);
		return (status);
	}
	return (status);
	//continue ;
}

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

char **to_env(char *cmd_name)
{
	int 		i;
	t_env_list	*env_lst;
	char		**env;
	int			size;
	char		**tmp;

	env_lst = g_data.env_lst;
	size = ft_envlstsize(env_lst) + 1;
	env = malloca(size * sizeof(char*));
	i = 0;
	while (env_lst)
	{
		tmp = ft_strjoin_alloca(env_lst->variable, "=", malloca);
		env[i] = ft_strjoin_alloca(tmp, env_lst->value, malloca);
		//printf("env[%s]\n", env[i]);
		i++;
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}
