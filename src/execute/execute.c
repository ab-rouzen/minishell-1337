/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/25 23:23:11 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2]);

int	execute(t_list *cmd_lst)
{
	int			childpid;
	int			stat_loc;
	int			(*piper)[2];
	int			i;
	t_list		*prev;

	if (builtin_cmd_only(cmd_lst))
		return (TRUE);
	piper = init_pipe(cmd_lst);
	i = 0;
	while (cmd_lst)
	{
		prev = cmd_lst;
		if (cmd_lst->next)
			pipe(piper[i + 1]);
		childpid = fork_cmd(cmd_lst, piper[i][0], &piper[i + 1]);
		if (cmd_lst->next)
			close(piper[i + 1][1]); // closed write end of the pipe
		i++;
		cmd_lst = cmd_lst->next;
	}
	if (waitpid(childpid, &stat_loc, WUNTRACED) != -1)
		child_exit_stat(TCMD(prev)->cmd_name, stat_loc);
	return (0);
}

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2])
{
	char	*cmd_path;

	if (cmd->next)
		close(pipe[0][0]);
	dup_pipe(fd_in, pipe[0][1]);
	if (set_redirection(cmd) == FALSE)
		exit(EXIT_FAILURE);
	if (ft_check_builtin(cmd))
		exit(ft_builtin(cmd));
	duplicate_redir_fd(cmd);
	if (check_cmd(cmd) == FALSE)
		exit(EXIT_FAILURE);
	cmd_path = ((t_cmd_lst*)cmd->content)->cmd_name;
	//printf("this is execve [%s]\n", cmd_path);
	execve(cmd_path, ((t_cmd_lst*)cmd->content)->cmd_args, to_env());
	perror("dumm");
	exit(EXIT_FAILURE);
}

int (*init_pipe(t_list *cmd_lst))[2]
{
	int	(*piper)[2];
	int	size;

	size = ft_lstsize(cmd_lst);
	//printf("sz is %d\n", size);
	piper = malloca(sizeof(int[size + 1][2]));
	piper[0][0] = 0;
	piper[size][1] = 1;
	piper[size][0] = 0;
	//printf("pipe is %d\n", piper[size - 1][0]);
	return (piper);
}

int	fork_cmd(t_list *cmd, int fd_in, int (*pipe_fd)[2])
{
	int	childpid;

	childpid = -1;
	// if (set_redirection(cmd) == FALSE)
	// 	return (FALSE);
	//printf("cmd pointer[%p]\n", cmd);
	//if (check_cmd(get_cmd_path(cmd), &cmd) == TRUE)
	//{
	// if (ft_check_builtin(cmd))
	// {
	// 	((t_cmd_lst*)(cmd->content))->fd_in = fd_in; 
	// 	((t_cmd_lst*)(cmd->content))->fd_out = pipe_fd[0][1];
	// 	ft_builtin(cmd);
	// }
	// else
	// {
	childpid = fork();
	if (childpid == 0)
		exec_child(cmd, fd_in, pipe_fd);
	//}
	//printf("parent: cmd pointer[%p]\n", cmd);
	close_hdoc_fd(cmd);
	if (get_redir_lst_heredoc_num(((t_cmd_lst*)cmd->content)->redir_lst))
		g_data.hdoc_cmd_no++;
	return (childpid);
}

void	dup_pipe(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		//ft_printf("in STDIN\n");
		//printf("pipe read end :%d\n", r = dup2(fd_in, STDIN_FILENO));
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		//ft_printf("in STDOUT\n");
		//printf("pipe write end :%d\n", w = dup2(fd_out, STDOUT_FILENO));
		(dup2(fd_out, STDOUT_FILENO), close(fd_out));
	}	
}