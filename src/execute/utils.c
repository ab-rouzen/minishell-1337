/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/25 23:14:23 by arouzen          ###   ########.fr       */
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
	if (cmd_name && *cmd_name)
		while (path[i])
		{
			tmp = ft_strjoin_alloca(path[i], "/", malloca);
			tmp = ft_strjoin_alloca(tmp, cmd_name, malloca);
			if (access(tmp, F_OK) == 0)
			{
				TCMD(cmd_lst)->cmd_name = tmp;
				//printf("accessed here: %s\n", tmp);
				return (free(path), TRUE);
			}
			i++;
		}
	return (free(path), FALSE);
}

int	check_cmd(t_list *cmd)
{
	if (TCMD(cmd)->cmd_name == NULL)
		return (FALSE);
	get_cmd_path(cmd);
	if (access(TCMD(cmd)->cmd_name, F_OK))
		return (print_error(TCMD(cmd)->cmd_name, CMD_NOT_FOUND), FALSE);
	if (is_dir(TCMD(cmd)->cmd_name))
		return (print_error(TCMD(cmd)->cmd_name, CMD_IS_DIR), FALSE);
	if (access(TCMD(cmd)->cmd_name, F_OK|X_OK))
		return(print_error(TCMD(cmd)->cmd_name, CMD_PERM), FALSE);
	return (TRUE);
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

char **to_env(void)
{
	int 		i;
	t_env_list	*env_lst;
	char		**env;
	int			size;
	char		*tmp;

	env_lst = g_data.env_lst;
	size = ft_envlstsize(env_lst) + 1;
	env = malloca(size * sizeof(char*));
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

void	child_exit_stat(char *cmd_name, int stat_loc)
{
	char	*tmp;

	if (WIFEXITED(stat_loc))
	{
		//printf("old exit status %d\n", g_data.exit_status);
		g_data.exit_status = WEXITSTATUS(stat_loc);
		//printf("exited with %d\n", g_data.exit_status);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		tmp = ft_itoa(WTERMSIG(stat_loc));
		print_error(cmd_name, ft_strjoin_alloca(": received signal ", tmp, malloca));
		free(tmp);
	}
	while(waitpid(-1, &stat_loc, WUNTRACED) > 0)
		;
}

void	print_error(char *cmd_name, char *msg)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

t_bool	is_dir(char *name)
{
	struct stat	f_stat;
	
	stat(name, &f_stat);
	return (!S_ISREG(f_stat.st_mode));
}
