/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/27 14:39:45 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/types.h"
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
		//printf("%d token\n", tok);
		if (cmd->fd_in != STDIN_FILENO)
		{
			close(cmd->fd_in);
		}
		cmd->fd_in = open_file(file, O_RDONLY, 0);
		//printf("fd is %d\n", cmd->fd_in);
	}
	else if (tok == TOK_REDI_O_APP || tok == TOK_REDI_O)
	{
		//printf("%d token\n", tok);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (tok == TOK_REDI_O_APP)
			cmd->fd_out = open_file(file, F_RED_OA, F_PERM);
		else
		{
			cmd->fd_out = open_file(file, O_CREAT | O_TRUNC | O_WRONLY, F_PERM);	
			//printf("fd is %d\n", cmd->fd_out);
			//ft_putendl_fd("bla bla", cmd->fd_out);
		}
	}
}

/*closes cmd fd io if non STD*/
void	close_io_fd(t_cmd_lst *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		//printf("%d input closed\n", cmd->fd_in);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		//printf("%d input closed\n", cmd->fd_in);
		close(cmd->fd_out);
	}
}

/*uses dup2 to duplicate command fd std io into the new assigned io*/
void	duplicate_redir_fd(t_cmd_lst *cmd)
{
	int in = dup2(cmd->fd_in, STDIN_FILENO);
	//printf("%d input duped from [%d]\n", in, TCMD(cmd_node)->fd_in);
	int out = dup2(cmd->fd_out, STDOUT_FILENO);
	//printf("%d out duped from [%d]\n", out, TCMD(cmd_node)->fd_out);
}
