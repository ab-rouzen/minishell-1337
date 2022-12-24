/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/24 17:34:44 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2]);

int	execute(t_list *cmd_lst)
{
	int			childpid;
	int			(*piper)[2];
	int			i;
	t_list		*cmd;

	cmd = cmd_lst;
	piper = init_pipe(cmd_lst);
	i = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(piper[i + 1]);
		childpid = fork_cmd(cmd, piper[i][0], &piper[i + 1]);
		if (cmd->next)
			close(piper[i + 1][1]); // closed write end of the pipe
		i++;
		cmd = cmd->next;
	}
	waitpid(childpid, NULL, WUNTRACED);
	//printf("%d: child returned\n", waitpid(childpid, NULL, WUNTRACED));
	return (0);
}

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2])
{
	char	*cmd_path;

	//int r,w;
	if (cmd->next)
		close(pipe[0][0]); //closed read end of the 1
	if (fd_in != STDIN_FILENO)
	{
		//ft_printf("in STDIN\n");
		//printf("pipe read end :%d\n", r = dup2(fd_in, STDIN_FILENO));
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (pipe[0][1] != STDOUT_FILENO)
	{
		//ft_printf("in STDOUT\n");
		//printf("pipe write end :%d\n", w = dup2(pipe[0][1], STDOUT_FILENO));
		(dup2(pipe[0][1], STDOUT_FILENO), close(pipe[0][1]));
	}
	// if (set_redirection(((t_cmd_lst*)cmd->content)->redir_lst) == FALSE)
	// 	exit(EXIT_FAILURE);
	// if (ft_check_builtin(((t_cmd_lst *)cmd->content)->cmd_name))
	// 	ft_builtin(cmd);
	//else
	//{
		duplicate_redir_fd(cmd);
		check_cmd(get_cmd_path(cmd), &cmd);
		cmd_path = ((t_cmd_lst*)cmd->content)->cmd_name;
		printf("this is execve [%s]\n", cmd_path);
		execve(cmd_path, ((t_cmd_lst*)cmd->content)->cmd_args, to_env());
	//}
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
	if (set_redirection(cmd) == FALSE)
		return (FALSE);
	//printf("cmd pointer[%p]\n", cmd);
	//if (check_cmd(get_cmd_path(cmd), &cmd) == TRUE)
	//{
	if (ft_check_builtin(cmd))
		ft_builtin(cmd);
	else
	{
		childpid = fork();
		if (childpid == 0)
			exec_child(cmd, fd_in, pipe_fd);
	}
	//printf("parent: cmd pointer[%p]\n", cmd);
	close_hdoc_fd(cmd);
	if (get_redir_lst_heredoc_num(((t_cmd_lst*)cmd->content)->redir_lst))
		g_data.hdoc_cmd_no++;
	return (childpid);
}
