/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 22:45:18 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*opens all files in redirection list and assign corresponding*/
/* fd to cmd list command fd io */
int	set_redirection(t_cmd_lst *cmd)
{
	int				index;
	t_list			*redir_lst;
	t_redir_list	*node;

	redir_lst = cmd->redir_lst;
	index = 0;
	while (redir_lst)
	{
		node = (t_redir_list *)redir_lst->content;
		if (node->tok == TOK_REDI_I)
			set_redir_fd(cmd, TOK_REDI_I, node->file);
		else if (node->tok == TOK_REDI_O)
			set_redir_fd(cmd, TOK_REDI_O, node->file);
		else if (node->tok == TOK_REDI_O_APP)
			set_redir_fd(cmd, TOK_REDI_O_APP, node->file);
		else if (node->tok == TOK_HEREDOC)
			cmd->fd_in = g_data.fd_heredoc[g_data.hdoc_cmd_no][index++];
		if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
			return (FALSE);
		redir_lst = redir_lst->next;
	}
	return (TRUE);
}

/*sets argument fd to new_fd and closes fd if non STD*/
void	set_redir_fd(t_cmd_lst *cmd, enum e_token tok, char *file)
{
	if (tok == TOK_REDI_I)
	{
		if (cmd->fd_in != STDIN_FILENO)
		{
			close(cmd->fd_in);
		}
		cmd->fd_in = open_file(file, O_RDONLY, 0);
	}
	else if (tok == TOK_REDI_O_APP || tok == TOK_REDI_O)
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (tok == TOK_REDI_O_APP)
			cmd->fd_out = open_file(file, O_CREAT | O_APPEND | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
		{
			cmd->fd_out = open_file(file, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
}

/*uses dup2 to duplicate command fd std io into the new assigned io*/
void	duplicate_redir_fd(t_cmd_lst *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
}
