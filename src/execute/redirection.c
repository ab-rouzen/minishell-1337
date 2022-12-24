/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 16:52:46 by arouzen          ###   ########.fr       */
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
		redir_node= (t_redir_list*)cmd->redir_lst->content;
		if (redir_node->tok == TOK_REDI_I)
			cmd->fd_in = open_file(redir_node->file, O_RDONLY, 0);
		if (redir_node->tok == TOK_REDI_O)
			cmd->fd_out = open_file(redir_node->file, O_CREAT|O_TRUNC|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		else if (redir_node->tok == TOK_REDI_O_APP)
			cmd->fd_out = open_file(redir_node->file, O_CREAT|O_APPEND|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		else if (redir_node->tok == TOK_HEREDOC)
			cmd->fd_in = g_data.fd_heredoc[g_data.hdoc_cmd_no][index++];
		if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
			return (FALSE);
		redir_lst = redir_lst->next;
	}
	//ft_printf("count: %d\n", index);
	//duplicate_redir_fd(fd_in, fd_out);
	return (TRUE);
}

void	duplicate_redir_fd(t_list *cmd_node)
{
	//printf("input: %d, duped to %d\n", fd_input, dup2(fd_input, STDIN_FILENO));
	//printf("output: %d, duped to %d\n", fd_output, dup2(fd_output, STDOUT_FILENO));
	dup2(((t_cmd_lst*)cmd_node->content)->fd_in, STDIN_FILENO);
	dup2(((t_cmd_lst*)cmd_node->content)->fd_out, STDOUT_FILENO);
}
