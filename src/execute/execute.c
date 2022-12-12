/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:21 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/12 22:33:02 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_list *cmd, int fd_in, int fd_out);

int	execute(t_list *cmd_lst)
{
	int			childPid;
	int			(*piper)[2];
	int			i;
	//t_list		*tmp;

	piper = malloca(sizeof(int[25][2]));
	piper[0][0] = 0;
	piper[2][1] = 1;
	i = 0;
	while (cmd_lst)
	{
		if (cmd_lst->next)
			pipe(piper[i + 1]);
		get_cmd_path(cmd_lst);
		if (((t_cmd_lst*)cmd_lst->content)->cmd_name == NULL)
		{
			printf("command not found\n");
			cmd_lst =cmd_lst->next;
			continue;
		}
		printf("pipe creation success: %d in | %d out \n", piper[0][1], piper[0][0]);
		childPid = fork();
		if (childPid == 0)
		{
			if (cmd_lst->next)
				close(piper[i + 1][0]); //closed read end of the 1
			exec_child(cmd_lst, piper[i][0], piper[i + 1][1]);
		}
		if (cmd_lst->next)
			close(piper[i + 1][1]); // closed write end of the pipe
		i++;
		wait(NULL);
		cmd_lst = cmd_lst->next;
	}
	printf("All exec'ed successfully\n");
	return (0);
}

void	exec_child(t_list *cmd, int fd_in, int fd_out)
{
	char	*cmd_path;

	int r,w;
	cmd_path = ((t_cmd_lst*)cmd->content)->cmd_name;
	printf("pipe read end :%d\n", r = dup2(fd_in, 0));
	printf("pipe write end :%d\n", w = dup2(fd_out, 1));
	execve(cmd_path, ((t_cmd_lst*)cmd->content)->cmd_args, NULL); // needs env lst function to char**
	puts("execve failed\n");
}