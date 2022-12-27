/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:11:43 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 18:12:35 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file_redir_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
	{
		perror(file);
		return (FD_ERROR);
	}
	return (fd_in);
}

int	open_file(char *file, int oflag, int perm)
{
	int	fd;

	fd = open(file, oflag, perm);
	if (fd == -1)
	{
		perror(file);
		return (FD_ERROR);
	}
	return (fd);
}

/*closes cmd fd io if non STD*/
void	close_io_fd(t_cmd_lst *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		close(cmd->fd_out);
	}
}
