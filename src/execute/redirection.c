/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/26 22:56:48 by arouzen          ###   ########.fr       */
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
	int	fd_in;

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
	t_cmd_lst		*cmd;
	t_list			*redir_lst;

	cmd = (t_cmd_lst *)cmd_lst->content;
	redir_lst = cmd->redir_lst;
	index = 0;
	while (redir_lst)
	{
		if (TRDIR(redir_lst)->tok == TOK_REDI_I)
			set_redir_fd(cmd, TOK_REDI_I, TRDIR(redir_lst)->file);
		else if (TRDIR(redir_lst)->tok == TOK_REDI_O)
			set_redir_fd(cmd, TOK_REDI_O, TRDIR(redir_lst)->file);
		else if (TRDIR(redir_lst)->tok == TOK_REDI_O_APP)
			set_redir_fd(cmd, TOK_REDI_O_APP, TRDIR(redir_lst)->file);
		else if (TRDIR(redir_lst)->tok == TOK_HEREDOC)
			set_redir_fd(&cmd->fd_in, 0, g_data.fd_heredoc \
			[g_data.hdoc_cmd_no][index++]);
		if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
			return (FALSE);
		redir_lst = redir_lst->next;
	}
	return (TRUE);
}

/*sets argument fd to new_fd and closes fd if non STD*/
void	set_redir_fd(t_list *cmd, enum e_token tok, char *file)
{
	if (tok == TOK_REDI_I)
	{
		if (TCMD(cmd)->fd_in != STDIN_FILENO)
		{
			//printf("%d input closed\n", *fd);
			close(TCMD(cmd)->fd_in);
		}
		TCMD(cmd)->fd_in = open_file(file, O_RDONLY, 0);
	}
	else if (tok == TOK_REDI_O_APP || tok == TOK_REDI_O)
	{
		if (TCMD(cmd)->fd_out != STDOUT_FILENO)
			close(TCMD(cmd)->fd_out);
		if (tok == TOK_REDI_O_APP)
			TCMD(cmd)->fd_out = open_file(file, F_RED_OA, F_PERM);
		else
			TCMD(cmd)->fd_out = open_file(file, F_RED_O, F_PERM);	
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
	dup2(TCMD(cmd_node)->fd_in, STDIN_FILENO);
	dup2(TCMD(cmd_node)->fd_out, STDOUT_FILENO);
}
