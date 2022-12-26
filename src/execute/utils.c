/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:35:05 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:48:13 by arouzen          ###   ########.fr       */
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

int	check_cmd(t_list *cmd)
{
	if (TCMD(cmd)->cmd_name == NULL)
		return (FALSE);
	get_cmd_path(cmd);
	if (access(TCMD(cmd)->cmd_name, F_OK))
		return (print_error(TCMD(cmd)->cmd_name, CMD_NOT_FOUND, 1), FALSE);
	if (is_dir(TCMD(cmd)->cmd_name))
		return (print_error(TCMD(cmd)->cmd_name, CMD_IS_DIR, 1), FALSE);
	if (access(TCMD(cmd)->cmd_name, F_OK | X_OK))
		return (print_error(TCMD(cmd)->cmd_name, CMD_PERM, 1), FALSE);
	return (TRUE);
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
