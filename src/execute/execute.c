/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/29 02:30:50 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2]);

int	execute(t_list *cmd_lst)
{
	int			childpid;
	int			i;
	int			(*piper)[2];

	g_data.exec = TRUE;
	if (builtin_cmd_only(cmd_lst))
		return (TRUE);
	i = 0;
	init_pipe(cmd_lst, &piper);
	while (cmd_lst)
	{
		childpid = fork_cmd(cmd_lst, piper[i][0], &piper[i + 1]);
		i++;
		if (cmd_lst->next == NULL)
			wait_child(childpid, cmd_lst);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2])
{
	char	*cmd_path;

	reset_signals();
	if (cmd->next)
		close(pipe[0][0]);
	dup_pipe(fd_in, pipe[0][1]);
	if (set_redirection(cmd->content) == FALSE)
		exit(EXIT_FAILURE);
	if (ft_check_builtin(cmd))
		exit(ft_builtin(cmd));
	duplicate_redir_fd(cmd->content);
	check_cmd(cmd->content);
	cmd_path = ((t_cmd_lst *)cmd->content)->cmd_name;
	execve(cmd_path, ((t_cmd_lst *)cmd->content)->cmd_args, to_env());
	print_error("Execve", "Failed", 1);
	exit(EXIT_FAILURE);
}

void	init_pipe(t_list *cmd_lst, int (**piper)[2])
{
	int	size;

	size = ft_lstsize(cmd_lst);
	*piper = malloca(sizeof(int [size + 1][2]));
	(*piper)[0][0] = 0;
	(*piper)[size][1] = 1;
	(*piper)[size][0] = 0;
}

int	fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2])
{
	int	childpid;

	childpid = -1;
	if (cmd->next)
		if (pipe(pipe_fd[0]) < 0)
			err_exit(EXIT_FAILURE, "Pipe failed");
	childpid = fork();
	if (childpid == 0)
		exec_child(cmd, fd_in, pipe_fd);
	else if (childpid < 0)
		err_exit(EXIT_FAILURE, "Fork failed");
	close_hdoc_fd(cmd);
	if (get_redir_lst_heredoc_num(((t_cmd_lst *)cmd->content)->redir_lst))
		g_data.hdoc_cmd_no++;
	if (cmd->next)
		close(pipe_fd[0][1]);
	if (fd_in != STDIN_FILENO)
		close (fd_in);
	return (childpid);
}

void	dup_pipe(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
