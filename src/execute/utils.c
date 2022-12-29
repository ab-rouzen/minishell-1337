/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 01:02:15 by arouzen          ###   ########.fr       */
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

int	check_cmd(t_cmd_lst *cmd)
{
	int	err;

	err = 0;
	if (cmd->cmd_name == NULL)
		return (FALSE);
	if (ft_strchr(cmd->cmd_name, '/') == NULL)
	{
		if (get_cmd_path(cmd) == FALSE)
			err = 1;
	}
	if (!err && access(cmd->cmd_name, F_OK | X_OK) == 0)
		return (TRUE);
	else if (err == 0)
		err = 2;
	if (err == 1)
		print_error(cmd->cmd_name, CMD_NOT_FOUND, 1);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->cmd_name);
	}
	return (FALSE);
}

/*prints error into STDERR [SH: 'cmd_name': 'msg']*/
void	print_error(char *cmd_name, char *msg, t_bool new_line)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (new_line)
		ft_putstr_fd("\n", STDERR_FILENO);
}

t_bool	is_dir(char *name)
{
	struct stat	f_stat;

	stat(name, &f_stat);
	return (!S_ISREG(f_stat.st_mode));
}

void	err_exit(int exit_status, char *err_msg)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(exit_status);
}
