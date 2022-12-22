/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:41:33 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/22 15:01:17 by arouzen          ###   ########.fr       */
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

int	set_redirection(t_list *redir_lst)
{
	enum 		e_token tok;
	char		*file;
	int			index;
	int			fd_in;
	int			fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	index = 0;
	while (redir_lst)
	{
		tok = ((t_redir_list*)redir_lst->content)->tok;
		file = ((t_redir_list*)redir_lst->content)->file;
		if (tok == TOK_REDI_I)
			fd_in = open_file(file, O_RDONLY, 0);
		if (tok == TOK_REDI_O)
			fd_out = open_file(file, O_CREAT|O_TRUNC|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		else if (tok == TOK_REDI_O_APP)
			fd_out = open_file(file, O_CREAT|O_APPEND|O_WRONLY, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		else if (tok == TOK_HEREDOC)
			fd_in = g_data.fd_heredoc[g_data.hdoc_cmd_no][index++];
		if (fd_in == FD_ERROR || fd_out == FD_ERROR)
			return (FALSE);
		redir_lst = redir_lst->next;
	}
	ft_printf("count: %d\n", index);
	duplicate_redir_fd(fd_in, fd_out);
	return (TRUE);
}

void	duplicate_redir_fd(int fd_input, int fd_output)
{
	printf("input: %d, duped to %d\n", fd_input, dup2(fd_input, STDIN_FILENO));
	printf("output: %d, duped to %d\n", fd_output, dup2(fd_output, STDOUT_FILENO));
}

/*closes heredoc file descriptors opened for the argument command*/
void	close_hdoc_fd(t_list *cmd)
{
	int			i;
	t_list		*redir_lst;

	i = 0;
	redir_lst = ((t_cmd_lst*)cmd->content)->redir_lst;
	while (redir_lst)
	{
		if (((t_redir_list*)redir_lst->content)->tok == TOK_HEREDOC)
			close(g_data.fd_heredoc[g_data.hdoc_cmd_no][i++]);
		redir_lst = redir_lst->next;
	}
}
