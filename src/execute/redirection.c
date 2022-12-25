/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/25 23:18:23 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file_redir_in(char *file)
{
	int fd_in;

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
	int fd_in;

	fd_in = open(file, oflag, perm);
	if (fd_in == -1)
	{
		perror(file);
		return (FD_ERROR);
	}
	return (fd_in);
}

/*opens all files in redirection list and assign corresponding*/
/* fd to cmd list command fd io */
int	set_redirection(t_list *cmd_lst)
{
	int				index;
	t_redir_list	*redir_node;
	t_cmd_lst		*cmd;
	t_list			*redir_lst;

	cmd = (t_cmd_lst*)cmd_lst->content;
	redir_lst = cmd->redir_lst;
	index = 0;
	while (redir_lst)
	{
		redir_node = (t_redir_list*)cmd->redir_lst->content;
		if (redir_node->tok == TOK_REDI_I)
			set_redir_fd(&cmd->fd_in, 0, open_file(redir_node->file, O_RDONLY, 0));
		else if (redir_node->tok == TOK_REDI_O)
			set_redir_fd(&cmd->fd_out, 1, open_file(redir_node->file, O_CREAT|O_TRUNC|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
		else if (redir_node->tok == TOK_REDI_O_APP)
			set_redir_fd(&cmd->fd_out, 1, open_file(redir_node->file, O_CREAT|O_APPEND|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
		else if (redir_node->tok == TOK_HEREDOC)
		{
			printf("hdoc: cmdno[%d] fd[%d] --- \n", g_data.hdoc_cmd_no, g_data.fd_heredoc[g_data.hdoc_cmd_no][index]);
			set_redir_fd(&cmd->fd_in, 0, g_data.fd_heredoc[g_data.hdoc_cmd_no][index++]);
		}
		if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
			return (FALSE);
		redir_lst = redir_lst->next;
	}
	return (TRUE);
}

/*sets argument fd to new_fd and closes fd if non STD*/
void	set_redir_fd(int *fd, int io, int new_fd)
{
	if (io == STDIN_FILENO)
	{
		if (*fd != STDIN_FILENO)
		{
			printf("%d input closed\n", *fd);
			close(*fd);
		}
		*fd = new_fd;
	}
	else if (io == STDOUT_FILENO)
	{
		if (*fd != STDOUT_FILENO)
			close(*fd);
		*fd = new_fd;
	}
}

/*closes cmd fd io if non STD*/
void	close_io_fd(t_list *cmd)
{
	if (TCMD(cmd)->fd_in != STDIN_FILENO)
	{
		//printf("%d input closed\n", TCMD(cmd)->fd_in);
		close(TCMD(cmd)->fd_in);
	}
	if (TCMD(cmd)->fd_out != STDOUT_FILENO)
	{
		//printf("%d input closed\n", TCMD(cmd)->fd_in);
		close(TCMD(cmd)->fd_out);
	}
}

/*uses dup2 to duplicate command fd std io into the new assigned io*/
void	duplicate_redir_fd(t_list *cmd_node)
{
	// printf("input: %d, duped to %d\n",TCMD(cmd_node)->fd_in , dup2(TCMD(cmd_node)->fd_in, STDIN_FILENO));
	// printf("output: %d, duped to %d\n", TCMD(cmd_node)->fd_out, dup2(TCMD(cmd_node)->fd_out, STDOUT_FILENO));
	dup2(TCMD(cmd_node)->fd_in, STDIN_FILENO);
	dup2(TCMD(cmd_node)->fd_out, STDOUT_FILENO);
}
