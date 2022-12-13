/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/13 18:06:43 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2]);

int	execute(t_list *cmd_lst)
{
	int			childPid;
	int			(*piper)[2];
	int			i;
	t_list		*cmd;

	cmd = cmd_lst;
	piper = malloca(sizeof(int[25][2]));
	piper[0][0] = 0;
	piper[2][1] = 1;
	i = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(piper[i + 1]);
		get_cmd_path(cmd);
		if (((t_cmd_lst*)cmd->content)->cmd_name == NULL)
		{
			printf("command not found\n");
			cmd = cmd->next;
			continue ;
		}
		printf("pipe creation success: %d in | %d out \n", piper[i + 1][1], piper[i + 1][0]);
		childPid = fork();
		if (childPid == 0)
			exec_child(cmd, piper[i][0], piper[i + 1]);
		if (cmd->next)
			close(piper[i + 1][1]); // closed write end of the pipe
		i++;
		wait(NULL);
		cmd = cmd->next;
	}
	return (0);
}

void	exec_child(t_list *cmd, int fd_in, int (*pipe)[2])
{
	char	*cmd_path;

	int r,w;
	if (cmd->next)
		close(pipe[0][0]); //closed read end of the 1
	cmd_path = ((t_cmd_lst*)cmd->content)->cmd_name;
	if (fd_in != STDIN_FILENO)
	{
		printf("pipe read end :%d\n", r = dup2(fd_in, 0));
		close(fd_in);
	}
	if (pipe[0][1] != STDOUT_FILENO)
	{
		printf("pipe write end :%d\n", w = dup2(pipe[0][1], 1));
		close(pipe[0][1]);
	}
	execve(cmd_path, ((t_cmd_lst*)cmd->content)->cmd_args, NULL); // needs env lst function to char**
	printf("execve failed\n");
}